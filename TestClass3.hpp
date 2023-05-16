//
//  TestClass3.hpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#ifndef TestClass3_hpp
#define TestClass3_hpp

#include <stdio.h>
#include <string>
#include "Storable.hpp"

namespace ECE141 {

  enum class Color {red, green, blue};

  class TestClass3 : public Storable {
  public:
    
    TestClass3(const std::string &aName, Color aColor, const char *aBuffer);
    virtual ~TestClass3();
    
    bool toJSON(std::ostream &aStream);

  protected:
    std::string name;
    char        initials[4];
    Color       color;
  };

}


#endif /* TestClass3_hpp */
