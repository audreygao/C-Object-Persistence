//
//  MetaFactory.cpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#include "Builder.hpp"
#include "JSONModel.hpp"
#include "Storable.hpp"
#include <vector>

namespace ECE141 {

  TestDocument* Builder::create(JSONModel &aModel) {
    
    TestClass1 * child1a;
    TestClass1 * child1b;
    TestClass2 * child2;
    TestClass3 * child3;
    float price;

    //get the member object's elementList -> varaible list of model
    JSONObject * obj = (JSONObject *)(aModel.elementList.at(1)->value);
    std::vector<JSONElement *> modelMemberList = obj->elementList;
    
    //iterate over all the variables through the elementList
    for(auto member: modelMemberList) {

      std::string memberName = member->key; //get the varaible name
      JSONObject * obj2 = (JSONObject *)(member->value);
      
      if(memberName == "child1a") {

        //get the elementList of the member object
        JSONObject * obj3 = (JSONObject *)(obj2->elementList.at(1)->value);
        std::vector<JSONElement *> objMemList = obj3->elementList;
        child1a = buildClass1(objMemList);
      } else if(memberName == "child1b") {
        //get the elementList of the member object
        JSONObject * obj3 = (JSONObject *)(obj2->elementList.at(1)->value);
        std::vector<JSONElement *> objMemList = obj3->elementList;
        child1b = buildClass1(objMemList);
      } else if(memberName == "child2") {
        //get the elementList of the member object
        JSONObject * obj3 = (JSONObject *)(obj2->elementList.at(1)->value);
        std::vector<JSONElement *> objMemList = obj3->elementList;
        child2 = buildClass2(objMemList);
      } else if(memberName == "child3") {
        //get the elementList of the member object
        JSONObject * obj3 = (JSONObject *)(obj2->elementList.at(1)->value);
        std::vector<JSONElement *> objMemList = obj3->elementList;
        child3 = buildClass3(objMemList);
      } else if(memberName == "price") {
        //typecast to get actual float value
        JSONPart * value = member->value;
        JSONFloatConst * floatConst = (JSONFloatConst *)value;
        price = floatConst->floatVal;
      }
    }

    return new TestDocument(*child1a, *child1b, *child2, *child3, price);
  }


  TestClass1 * Builder::buildClass1(std::vector<JSONElement *> list) {
    std::string name;
    int         count;
    float       amount;
    bool        used;  
    for(auto member: list) {
      std::string memberName = member->key; //get the varaible name
      JSONPart * value = member->value;

      //determine the varibale
      if(memberName == "name") {
        JSONStrConst * str = (JSONStrConst *)value; //typecast to get constant value
        name = str->strVal;
      } else if(memberName == "count") {
        JSONFloatConst * floatConst = (JSONFloatConst *)value; //typecast to get constant value
        count = floatConst->floatVal;
      } else if(memberName == "amount") {
        JSONFloatConst * floatConst = (JSONFloatConst *)value; //typecast to get constant value
        amount = floatConst->floatVal;
      } else if(memberName == "used") {
        JSONBoolConst * boolConst = (JSONBoolConst *)value; //typecast to get constant value
        used = boolConst->boolVal;
      }

    }
    return new TestClass1(name, used, amount, count);
  }

  TestClass2 * Builder::buildClass2(std::vector<JSONElement *> list) {
    
    std::string name;
    size_t      size;
    Metadata    meta;

    //iterate over all the variable members of TestClass2
    for(auto member: list) {
      std::string memberName = member->key; //get the varaible name
      JSONPart * value = member->value;

      //determine which varaible it is
      if(memberName == "name") {
        JSONStrConst * str = (JSONStrConst *)value;
        name = str->strVal;
      } else if(memberName == "size") {

        //typecast to get the actual float value
        JSONFloatConst * floatConst = (JSONFloatConst *)value;
        size = (size_t)floatConst->floatVal;
      } else if(memberName == "meta") {
        char    prop1;
        uint8_t prop2;
        bool    prop3;

        //typecast to the get element list of the member object of Metadata
        JSONObject * obj2 = (JSONObject *)(member->value);
        JSONObject * obj3 = (JSONObject *)(obj2->elementList.at(1)->value);
        std::vector<JSONElement *> structMemberList = obj3->elementList;

        //iterate over the variable elements of Metadata struct
        for(auto member: structMemberList) {
          std::string memberName = member->key; //get the varaible name
          JSONPart * value = member->value;

          //determine which struct member it is
          if(memberName == "prop1") {
            JSONStrConst * strConst = (JSONStrConst *)value; //typecast to get string value
            std::string s = strConst->strVal;
            prop1 = s.at(0); //convert to char
          } else if(memberName == "prop2") {
            JSONFloatConst * floatConst = (JSONFloatConst *)value; //typecast to get float value
            prop2 = (uint8_t)floatConst->floatVal;
          } else if(memberName == "prop3") {
            JSONBoolConst * boolConst = (JSONBoolConst *)value; //typecast to get boolean value
            prop3 = boolConst->boolVal;
          }
        }
        meta = ECE141::Metadata{prop1, prop2, prop3}; //initialize the Metadata struct
      } 
    }
    return new TestClass2(name, size, meta);
  }

  TestClass3 * Builder::buildClass3(std::vector<JSONElement *> list) {
    std::string name;
    char        initials[4];
    Color       color;
    for(auto member: list) {
      std::string memberName = member->key; //get the variable name
      JSONPart * value = member->value;

      //determine which variable it is
      if(memberName == "name") {
        JSONStrConst * strConst = (JSONStrConst *)value; //typecast the JSONPart
        name = strConst->strVal;
      } else if(memberName == "initials") {
        JSONStrConst * strConst = (JSONStrConst *)value; //typecast the JSONPart
        for(int i = 0; i < 3; i++) {
          initials[i] = strConst->strVal.at(i);
        }
      } else if(memberName == "color") {

        //typecast the JSONPart to get the color string
        JSONStrConst * str = (JSONStrConst *)value; 
        std::string colorStr = str->strVal;

        //deterine the JSONType
        if(colorStr == "red") {
          color = Color::red;
        } else if (colorStr == "green") {
          color = Color::green;
        } else if (colorStr == "blue") {
          color = Color::blue;
        }
      }
    }
    return new TestClass3(name, color, initials);
  }

}
