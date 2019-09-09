//
//  NotImplementedException.hpp
//  
//
//  Created by Wenjie Bai on 2/7/19.
//

#ifndef NotImplementedException_hpp
#define NotImplementedException_hpp

#include <stdio.h>
#include <string>
using namespace std;

class NotImplementedException{

private:
    string errMsg;

public:
    NotImplementedException(const string& message)
        :errMsg(message) { }
    string getError() {return errMsg;}

};
#endif /* NotImplementedException_hpp */
