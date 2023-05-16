//
//  JSONModel.hpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#ifndef JSONModel_hpp
#define JSONModel_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>

namespace ECE141 {

  enum class TokenType {
    openObject, openList, closeList, closeObject,
    constant, quoted, colon, unknown};

  enum class JSONType {object, list, element, constant, unknown};

  //-----------------------------

  struct JSONPart {
    JSONPart(JSONType aType) : type(aType) {}
    virtual ~JSONPart() {}
    virtual void debugDump(std::ostream &anOutput, int indent=0);
    virtual void add(){}

    JSONType type;

  };

  //JSONPart for float, boolean, and string values (constant)
  struct JSONStrConst : public JSONPart {
    JSONStrConst(const std::string &aValue)
      : JSONPart(JSONType::constant), strVal(aValue) {}
    virtual void debugDump(std::ostream &anOutput, int anIndent=0);
    std::string strVal;
  };
  struct JSONFloatConst : public JSONPart {
    JSONFloatConst(const float &aValue)
      : JSONPart(JSONType::constant), floatVal(aValue) {}
    virtual void debugDump(std::ostream &anOutput, int anIndent=0);
    float floatVal;
  };
  struct JSONBoolConst : public JSONPart {
    JSONBoolConst(const bool &aValue)
      : JSONPart(JSONType::constant), boolVal(aValue) {}
    virtual void debugDump(std::ostream &anOutput, int anIndent=0);
    bool boolVal;
  };

  //-----------------------------

  class JSONElement : public JSONPart {
  public:

    JSONElement(const std::string &aKey, JSONPart *aValue=nullptr);
    ~JSONElement();
    using JSONPart::add;
    void add(JSONPart * part);
    void debugDump(std::ostream &anOutput, int indent=0);

    std::string key;
    JSONPart *value;
  };

  //-----------------------------

  class JSONList : public JSONPart {
  public:
    JSONList(const std::string &aName);
    ~JSONList();
    using JSONPart::add;
    void add(JSONPart * part);
    void debugDump(std::ostream &anOutput, int indent=0);

    std::string name;
    std::vector<JSONPart *> list;
    //STUDENT: add something to hold list of items...
  };

  //-----------------------------

  class JSONObject : public JSONPart{
  public:

    JSONObject(const std::string &aName);
    ~JSONObject();
    using JSONPart::add;
    void add(JSONElement * part);
    void debugDump(std::ostream &anOutput, int indent=0);

    std::string name;
    std::vector<JSONElement *> elementList;
    //STUDENT: add something to hold key value pairs...
  };

  class JSONModel : public JSONPart {
  public:
    JSONModel();
    ~JSONModel();
    using JSONPart::add;
    void add(JSONElement * part);
    void debugDump(std::ostream &anOutput, int indent=0);
    //STUDENT: implement these methods...
    std::vector<JSONElement *> elementList; 
    };
 

}
#endif /* JSONModel_hpp */
