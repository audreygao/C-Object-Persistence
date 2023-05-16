//
//  MetaFactory.hpp
//  RGAssignment3
//
//  Created by rick gessner on 2/8/21.
//

#ifndef Builder_hpp
#define Builder_hpp

#include <stdio.h>
#include "JSONModel.hpp"
#include "TestDocument.hpp"

namespace ECE141 {
    
  class Builder {
  public:
    static TestDocument* create(JSONModel &aModel);
    static TestClass1 * buildClass1(std::vector<JSONElement *> list);
    static TestClass2 * buildClass2(std::vector<JSONElement *> list); 
    static TestClass3 * buildClass3(std::vector<JSONElement *> list);     
  };
}

#endif /* Builder_hpp */
