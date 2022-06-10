#ifndef UTIL_H
#define UTIL_H
#include<string>
using std::string;

//(\\n)|(\\t)|(\\\\)|(\\')|(\\a)|(\\f)|(\\r)|(\\b)|(\\v)|(\\0)|(\\\")
char specialCharacterValue(string str){
    // \"
    if(str=="\\\""){
        return '\"';
    }
    else if(str=="\\0"){
        return '\0';
    }
    else if(str=="\\v"){
        return '\v';
    }
    else if(str=="\\b"){
        return '\b';
    }
    else if(str=="\\r"){
        return '\r';
    }
    else if(str=="\\f"){
        return '\f';
    }
    else if(str=="\\a"){
        return '\a';
    }
    else if(str=="\\'"){
        return '\'';
    }
    else if(str=="\\\\"){
        return '\\';
    }
    else if(str=="\\t"){
        return '\t';
    }
    else if(str=="\\n"){
        return '\n';
    }
    return 0;
}

#endif