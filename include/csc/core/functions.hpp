#ifndef CSC_CORE_FUNCTIONS_HPP
#define CSC_CORE_FUNCTIONS_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/alias.hpp"

CSC_BEGIN

inline std::vector<CscStr> splitPath(ConstStr path){
    std::vector<CscStr> items;
    size_t pos = 0;

    if(pos == path.find('/')){                  //如果path的首个字符为/，即path为绝对路径时
        items.push_back("/");
        ++pos;
    }

    while(pos < path.size()){
        auto nxpos = path.find('/', pos);
        if(nxpos == CscStr::npos){       //如果path没有更多/时，那么剩余的部分就直接作为作用域或变量名称
            items.push_back(path.substr(pos, path.size() - pos));
            break;
        }

        if(nxpos == pos){                     //如果出现连续的/
            items.push_back("");
            pos = nxpos + 1;
            continue;
        }
        
        items.push_back(path.substr(pos, nxpos - pos));
        pos = nxpos + 1;
    }

    return items;
}

inline std::pair<CscStr, CscStr> detachName(ConstStr path){
    auto pos = path.rfind('/');

    if(pos == CscStr::npos){                       //当path不包含任何/，即path仅是作用域或变量名时
        return {"", path};
    }

    if(pos != 0 && pos != path.size() - 1){  //如果/不在path开头或结尾时，直接从/所在的位置分割
         return {path.substr(0, pos), path.substr(pos + 1)};
    }

    if(pos == 0 && path.size() > 1){          //如果/仅存在于path开头
        return {"/", path.substr(pos + 1)};
    }

    if(pos == path.size() - 1 && path.size() > 1){  //如果/存在于末尾
        return {path.substr(0, pos), ""};
    }

    return {"", ""};
}

CSC_END
#endif