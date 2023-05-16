//
//  Document.hpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#ifndef TestDocument_h
#define TestDocument_h

#include <vector>

#include "TestClass1.hpp"
#include "TestClass2.hpp"
#include "TestClass3.hpp"

namespace ECE141 {
    
  class TestDocument : public Storable {
  public:

    TestDocument() :
        child1a("oneA",false,3.14,1234),
        child1b("oneB",true,6.28, 567),
        child2("two", 99, ECE141::Metadata{'A',42,true}),
        child3("three", Color::red, "RKG")
    {
        price=35.99;
    };

    TestDocument(TestClass1 &oneA, TestClass1 &oneB, TestClass2 &two, TestClass3 &three, float p=35.99) : TestDocument(){
      child1a = oneA;
      child1b = oneB;
      child2 = two;
      child3 = three;
      price = p;
    }
    
    ~TestDocument() {}

    virtual bool toJSON(std::ostream &aStream) {
      aStream << "{\n";
      writeMeta(aStream, "TestDocument");

      //write member object
      aStream << '"' << "members" << '"' << " : { \n";      
      
      //object data members
      //1a
      aStream << '"' << "child1a" << '"' << ": ";
      bool oneA = child1a.toJSON(aStream);

      aStream << ",\n";
      //1b
      aStream << '"' << "child1b" << '"' << ": ";
      bool oneB = child1b.toJSON(aStream);

      aStream << ",\n";
      //2
      aStream << '"' << "child2" << '"' << ": ";
      bool two = child2.toJSON(aStream);

      aStream << ",\n";
      //3
      aStream << '"' << "child3" << '"' << ": ";
      bool three = child3.toJSON(aStream);

      aStream << ",\n";  

      //intrinsic data member price
      writeKeyValue(aStream, "price", price);

      aStream << "}\n"; 

      aStream << "}";
      return oneA && oneB && two && three;
    }
    
  protected:
    TestClass1 child1a;
    TestClass1 child1b;
    TestClass2  child2;
    TestClass3  child3;
    float price;
  };

}

#endif /* TestDocument_h */
