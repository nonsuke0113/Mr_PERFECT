//
//  StringUtil.h
//  gameTest-mobile
//
//  Created by 健介 丹野 on 2019/01/20.
//

#ifndef StringUtil_h
#define StringUtil_h

#include <string>

using namespace std;

class StringUtil
{
    static int lenByte(unsigned char c)
    {
        if ((c >= 0x00) && (c <= 0x7f))
        {
            return 1;
        }
        else if ((c >= 0xc2) && (c <= 0xdf))
        {
            return 2;
        }
        else if ((c >= 0xe0) && (c <= 0xef))
        {
            return 3;
        }
        else if ((c >= 0xf0) && (c <= 0xf7))
        {
            return 4;
        }
        
        return 0;
    }
    
public:
    
    static int lenUtf8(std::string &str)
    {
        auto _pstr = str.c_str();
        
        int i = 0;
        int len = 0;
        
        while (_pstr[i] != '\0')
        {
            len++;
            i += lenByte(_pstr[i]);
        }
        
        return len;
    }
};

#endif /* StringUtil_h */
