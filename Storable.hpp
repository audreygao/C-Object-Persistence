//
//  Storable.hpp
//  Assignment3
//
//  Created by rick gessner on 2/6/21.
//

#ifndef Storable_h
#define Storable_h
#include <iostream>
#include <iomanip> 
#include <string>
#include <sstream>

namespace ECE141 {
  
  class Storable {
  public:
    virtual bool toJSON(std::ostream &aStream)=0;

    //
    template <typename T>
    void writeKeyValue(std::ostream &aStream, const std::string &aKey,
                            const T& aValue)  {
      aStream << '"' << aKey << '"' << ": " << aValue <<" \n";
    }

    //for boolean
    void writeKeyValue(std::ostream &aStream, const std::string &aKey,
                            const bool & aValue)  {
      static const char* theKeys[]={"false","true"};
      aStream << '"' << aKey << '"' << ": " << theKeys[aValue] << " \n";
    }

    //for string
    void writeKeyValue(std::ostream &aStream, const std::string &aKey,
                            const std::string & aValue)  {
    aStream << '"' << aKey << '"' << ':' << '"' << aValue << '"' << " \n";
    }

    //write the meta info of the class
    void writeMeta(std::ostream &aStream, const std::string &name) {
      //aStream << "meta: {\n";
      aStream << '"' << "meta" << '"' << ": { \n";
      writeKeyValue(aStream, "class", name);
      aStream << ", \n";

      //set precision for version 1.0
      std::stringstream str;
      str << std::fixed << std::setprecision(1) << 1.0f ;
      aStream << '"' << "version" << '"' << ':' << str.str() << "\n";

      aStream << "},\n";
    }
};

}

#endif /* Storable_h */
