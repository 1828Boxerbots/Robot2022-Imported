#include <iostream>
#include "Constants.h"
namespace ArrayTest{
    bool in(std::string test, const std::string* array){
        for(int i =0 ; i < sizeof(array)/sizeof(array[0]); i++){
                if(array[i]==test){
                    return true;
                    }
            }
        return false;
        }
    }