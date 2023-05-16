//
//  TestClass1.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass1.hpp"
#include <vector>

namespace ECE141 {

  TestClass1::TestClass1(const std::string &aName,
                         bool aUsed, float anAmount, int aCount)
    : name(aName), used(aUsed), amount(anAmount), count(aCount) {}

  TestClass1::~TestClass1() {}

  bool TestClass1::toJSON(std::ostream &aStream) {
    aStream << "{\n";
    writeMeta(aStream, "TestClass1");
   
    //write member object
    aStream << '"' << "members" << '"' << " : { \n";
    writeKeyValue(aStream, "name", name);
    aStream << ", \n";
    writeKeyValue(aStream, "count", count);
    aStream << ", \n";
    writeKeyValue(aStream, "amount", amount);
    aStream << ", \n";
    writeKeyValue(aStream, "used", used);
    aStream << "}\n";        

    aStream << "}\n";
    return true;
  }

}
