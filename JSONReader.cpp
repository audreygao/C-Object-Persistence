//
//  JSONReader.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "JSONReader.hpp"
#include <cctype>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <cstring>


namespace ECE141 {

  using parseCallback = bool(char aChar);

  bool isWhitespace(char aChar) {
    static const char* theWS = " \t\r\n\b\xff";
    return strchr(theWS,aChar);
  }

  bool isColon(char aChar) {return kColon==aChar ? true  : false;}
  bool isComma(char aChar) {return kComma==aChar ? true  : false;}
  bool isQuote(char aChar) {return kQuote==aChar ? true  : false;}
  bool isContant(char aChar) {return isalnum(aChar) || '.'==aChar;}

  //------------------------------------------------------

  JSONReader::JSONReader(JSONModel &aModel, std::istream &anInput) : JSONParser(anInput), model(aModel) {
    anInput >> std::skipws;
  }
  
  //-----------------------------------------------------
  //determines the token type of the char (already implemented)
  TokenType determineType(char aChar) {
    const char* kConstantChars="01234567890tf";
    switch(aChar) {
      case kQuote: return TokenType::quoted;
      case kColon: return TokenType::colon;
      case kBraceOpen: return TokenType::openObject;
      case kBracketOpen: return TokenType::openList;
      case kBraceClose: return TokenType::closeObject;
      case kBracketClose: return TokenType::closeList;
      default:
        return strchr(kConstantChars, aChar)
          ? TokenType::constant : TokenType::unknown;
    }
    return TokenType::unknown;
  }

  //--- handle the goo inside our container ------------------

  bool JSONReader::parseElements(char aChar) {
    bool theResult=true;
    
    TokenType theType = determineType(aChar);
    std::string temp;

    switch(theType) {
      case TokenType::openObject: {//object is a value

        //if parent is not null and a list or element, create and add the JSONObject
        if(!elementStack.empty() &&
           (elementStack.top()->type == JSONType::list || 
            elementStack.top()->type == JSONType::element)) {
          JSONObject * obj = new JSONObject("1");

          //typecast depending on the type and add the object to the parent 
          if(elementStack.top()->type == JSONType::list) {
            JSONList * list = (JSONList *)(elementStack.top());
            list->add(obj);
          } else {
            JSONElement * ele = (JSONElement *)(elementStack.top());
            ele->add(obj);
          }

          //push the JSONObject onto the stack
          elementStack.push(obj);
        } else { //doesn't match grammatical rules
          theResult = false;
        }
        break;
      }
      case TokenType::openList: {//list is a value

        //if parent is not null and a list or element, create and add the JSONList
        if(!elementStack.empty() &&
           (elementStack.top()->type == JSONType::list || 
            elementStack.top()->type == JSONType::element)) {
          
          //typecast depending on the type and add the list to the parent 
          JSONList * li = new JSONList("?");
          if(elementStack.top()->type == JSONType::list) {
            JSONList * list = (JSONList *)(elementStack.top());
            list->add(li);
          } else {
            JSONElement * ele = (JSONElement *)(elementStack.top());
            ele->add(li);
          }

          //push the JSONObject onto the stack
          elementStack.push(li);
        } else { //doesn't match grammatical rules
          theResult = false;
        }
        break;
      }
      case TokenType::closeList: {
        //pop JSONList (only if it is) off the stack
        if(!elementStack.empty() && elementStack.top()->type == JSONType::list) {
          elementStack.pop();
          //if the list is value of an element, element is done so pop it off the stack
          if(!elementStack.empty() && elementStack.top()->type == JSONType::element) {
            elementStack.pop();
          }

        } else {
          theResult = false;
        }
        break;
      }
      case TokenType::closeObject: {

        //pop JSONObject (if it is) off the stack
        if(!elementStack.empty() && elementStack.top()->type == JSONType::object) {
          elementStack.pop();

          //if the object is value of an element, element is done so pop it off the stack
          if(!elementStack.empty() && elementStack.top()->type == JSONType::element) {
            elementStack.pop();
          }
        } else {
          theResult = false;
        }
        break;
      }
      case TokenType::quoted: {
        temp = readUntil(isQuote, false); //get the quoted string
        skipIfChar(kQuote);

        //if parent is not null and a list or element -> a value
        if(!elementStack.empty()) {
          if(elementStack.top()->type == JSONType::list || 
            elementStack.top()->type == JSONType::element) {
            JSONStrConst * strConst = new JSONStrConst(temp);
            
            //typecast parent depending on the type and add the stringconst json to the parent 
            if(elementStack.top()->type == JSONType::list) {
              JSONList * list = (JSONList *)(elementStack.top());
              list->add(strConst);
            } else {
              JSONElement * ele = (JSONElement *)(elementStack.top());
              ele->add(strConst);
            }

            //if the string is value of an element, element is done so pop it off the stack
            if(!elementStack.empty() && elementStack.top()->type == JSONType::element) {
              elementStack.pop();
            }

          } else { //if parent is a JSONObject -> should be a key
            skipWhile(isWhitespace);
            if(!input.eof() && isColon(input.get())) { //element only if it's followed by a colon
              JSONElement * element = new JSONElement(temp);

              //typecast the parent to model or object and add the element to it
              if(elementStack.size() == 1 ) {
                JSONModel * tmpObj = &model;
                tmpObj->add(element);
              } else {
                JSONObject * tmpObj = (JSONObject *)elementStack.top();
                tmpObj->add(element);
              }
              elementStack.push(element);
            } else {
              theResult = false;
            }
          }
        } else{ //doesn't match grammatical rules
          theResult = false;
        }
        break;
      }     
      case TokenType::constant: {
        //get the constant
        temp=readWhile(isContant, false);
        temp.insert(0, 1, aChar);

        //if parent is list or element: it's valid as a value
        if(!elementStack.empty() &&
           (elementStack.top()->type == JSONType::list || 
            elementStack.top()->type == JSONType::element)) {

          //boolean constant
          if(aChar == 't' || aChar == 'f') {
            bool val = aChar=='t'? true : false;
            JSONBoolConst * boolConst = new JSONBoolConst(val);

            //determine the type of parent and typecast it, then add the boolean constant to parent
            if(elementStack.top()->type == JSONType::list) {
              JSONList * list = (JSONList *)(elementStack.top());
              list->add(boolConst);
            } else {
              JSONElement * ele = (JSONElement *)(elementStack.top());
              ele->add(boolConst);
            }

          } else { //not boolean -> numerial constant
            float f1= std::stof(temp); 
            JSONFloatConst * floatConst = new JSONFloatConst(f1);

            //determine and typecast parent, then add numerical constant to parent
            if(elementStack.top()->type == JSONType::list) {
              JSONList * list = (JSONList *)(elementStack.top());
              list->add(floatConst);
            } else {
              JSONElement * ele = (JSONElement *)(elementStack.top());
              ele->add(floatConst);
            }
          }

          //parent is element meaning element building is done, so pop it from stack
          if(!elementStack.empty() && elementStack.top()->type == JSONType::element) {
            elementStack.pop();
          }

        } else { //not valid
          theResult = false;
        }

        break;
      }
      case TokenType::colon: {
        //if parent is not element, not valid
        if(elementStack.top() == nullptr || elementStack.top()->type != JSONType::element ) {
          theResult = false;
        }
        break; //likely between key/value
      }  
      default: {
        theResult = false;
        break;
      }
    }
    
    skipWhile(isWhitespace);
    return theResult;
  }
  
//--------------------------------------------------------------------

  bool JSONReader::willTokenize() {
    if(!input.eof())  { //input stream is not empty
      char firstChar = input.get();
      if(  determineType(firstChar) == TokenType::openObject ) { //first char is open brace
        //push model onto stack
        elementStack.push(&model);
        return true;
      }
    }    
    return false;
  }

  //--------------------------------------------------------------------

  bool JSONReader::tokenize() {
    if(willTokenize()) {
      bool isValid=true;

      while(isValid) {
        skipWhile(isWhitespace);
        if(!input.eof()) {
          char theChar=input.get();
          isValid = parseElements(theChar);
          skipWhile(isWhitespace);
          skipIfChar(kComma);
        }
        else {
          break;
        }
      }
      return didTokenize(isValid);
    }
    return true;
  }

  //-----------------------------------------------------------

  bool JSONReader::didTokenize(bool aState) {
    return aState && elementStack.empty(); //all elements are valid and successfully added and popped
  }
  

}
