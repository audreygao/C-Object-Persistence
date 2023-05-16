//
//  TestClass3.cpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#include <cstring>
#include "TestClass3.hpp"

namespace ECE141 {

  TestClass3::TestClass3(const std::string &aName,
                         Color aColor, const char *aBuf)
    : name(aName), color(aColor) {      
      std::strncpy(initials, aBuf,3);
    }

  TestClass3::~TestClass3() {}

  bool TestClass3::toJSON(std::ostream &aStream) {

    aStream << "{\n";
    writeMeta(aStream, "TestClass3");

    //write member object
    aStream << '"' << "members" << '"' << " : { \n";
    writeKeyValue(aStream, "name", name) ;
    aStream << ", \n";
    std::string str(initials, 3);         
    writeKeyValue(aStream, "initials", str);
    aStream << ", \n";

    //determine the color type and write corresponding string to JSON
    switch (color)
    {
      case Color::red: {

        std::string str(std::string("red"));
        writeKeyValue(aStream, "color", str);
        break;
      }
      case Color::green: {

        std::string str(std::string("green"));
        writeKeyValue(aStream, "color", str);
        break;
      }
      case Color::blue: {

        std::string str(std::string("blue"));
        writeKeyValue(aStream, "color", str);
        break;
      }
      default: {
        return true;
        break;
      }
    }

    aStream << "}\n";
    aStream << "}\n";
    return true;
  }


}
