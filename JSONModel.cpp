//
//  JSONModel.cpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#include "JSONModel.hpp"

namespace ECE141 {
  
  void JSONPart::debugDump(std::ostream &anOutput, int anIndent) {
  }

  //template <typename T>
  void JSONStrConst::debugDump(std::ostream &anOutput, int anIndent) {
    anOutput << strVal;
    anOutput << "\n";
  }
  //void JSONIntConst::debugDump(std::ostream &anOutput, int anIndent) {}
  void JSONFloatConst::debugDump(std::ostream &anOutput, int anIndent) {
    anOutput << floatVal;
    anOutput << "\n";
  }
  void JSONBoolConst::debugDump(std::ostream &anOutput, int anIndent) {
    std::string str = (boolVal) ? "true" : "false";
    anOutput << str;
    anOutput << "\n";
  }

  //OCF
  JSONElement::JSONElement(const std::string &aKey,
                           JSONPart *aValue)
    : JSONPart(JSONType::element), key(aKey), value(aValue) {}
  JSONElement::~JSONElement(){
    delete value;
  }

  //OCF
  JSONList::JSONList(const std::string &aName)
    : JSONPart(JSONType::list) {}
  JSONList::~JSONList() {
    for(auto item: list) {
      delete item;
    }
  }

  //OCF
  JSONObject::JSONObject(const std::string &aName) : JSONPart(JSONType::object) {}
  JSONObject::~JSONObject() {
    for(auto item: elementList) {
      delete item;
    }
  }
   
  //JSONModel OCF
  JSONModel::JSONModel() : JSONPart(JSONType::object) {}
  JSONModel::~JSONModel() {
    for(auto item: elementList) {
      delete item;
    }
  }

//debugDump for different JSONPart
  void JSONElement::debugDump(std::ostream &anOutput, int indent) {
    for(int i = 0; i < indent; i++) {
      anOutput << " ";
    }
    anOutput << key << "=";
    value->debugDump(anOutput, indent + 2);
  }
  void JSONList::debugDump(std::ostream &anOutput, int indent) {
    anOutput << "[";
    for(auto item: list) {
      item->debugDump(anOutput, indent);
    }
    anOutput << "]";
    anOutput << "\n";
  }
  void JSONObject::debugDump(std::ostream &anOutput, int indent) {
    anOutput << "(Object):\n";
    for(auto item: elementList) {
      item->debugDump(anOutput, indent);
    }
  }
  void JSONModel::debugDump(std::ostream &anOutput, int indent) {
    anOutput << "(Object):\n";
    for(auto item: elementList) {
      item->debugDump(anOutput, indent);
    }
  }

  //assign the value to the element
  void JSONElement::add(JSONPart * part) {
    value = part;
  }

  //add element to the elementList
  void JSONObject::add(JSONElement * part) {
    elementList.push_back(part);
  }

  //add element to the elementList
  void JSONModel::add(JSONElement * part) {
    elementList.push_back(part);
  }

  //add the value to the list
  void JSONList::add(JSONPart * part) {
    list.push_back(part);
  }
    
}
