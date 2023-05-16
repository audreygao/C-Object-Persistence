//
//  TestClass2.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include "TestClass2.hpp"

namespace ECE141 {

  TestClass2::TestClass2(const std::string &aName, size_t aSize,
                         const Metadata &aMeta) : 
    name(aName), size(aSize) {
      meta.prop1=aMeta.prop1;
      meta.prop2=aMeta.prop2;
      meta.prop3=aMeta.prop3;
  }
  
  TestClass2::~TestClass2() {}

  bool TestClass2::toJSON(std::ostream &aStream) {
    aStream << "{\n";
    writeMeta(aStream, "TestClass2");
    
    //write member object
    aStream << '"' << "members" << '"' << " : { \n"; 
        writeKeyValue(aStream, "name", name);
        aStream << ", \n";
        writeKeyValue(aStream, "size", size);
        aStream << ", \n";       
        encodeStruct(aStream);
    aStream << "}\n";

    aStream << "}\n";
    return true;
  }

  //helper method to encode Metadata struct
  void TestClass2::encodeStruct(std::ostream &aStream) {
    aStream << '"' << "meta" << '"' << ": { \n";

    writeMeta(aStream, "Metadata");
    aStream << '"' << "members" << '"' << " : { \n"; 

    std::string str(1, meta.prop1);
    writeKeyValue(aStream, "prop1", str);
    aStream << ", \n";
    writeKeyValue(aStream, "prop2", (int)meta.prop2);
    aStream << ", \n";
    writeKeyValue(aStream, "prop3", meta.prop3);

    aStream << "}\n";

    aStream << "} \n";
  }

}
