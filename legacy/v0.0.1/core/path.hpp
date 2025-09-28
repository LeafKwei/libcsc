#ifndef CSC_PATH_HPP
#define CSC_PATH_HPP

#include <vector>
#include <tuple>
#include <array>
#include <cstring>
#include "csc/csc.hpp"
#include "csc/alias.hpp"

CSC_BEGIN

extern const char *builtinPaths[];
std::tuple<CscStr,CscStr> separatePath(const CscStr &path);
std::vector<CscStr> splitPath(const CscStr &path);

//=============== inline ===============
inline bool isEmptyPath(const CscStr &path){ 
    return path.size() == 0; 
}

inline int indexOfBuiltinPath(const CscStr &path){
     for(int index = 0; strlen(builtinPaths[index]) > 0; index++){
        if(path == builtinPaths[index]){
            return index;
        }
    }

    return -1;
}

inline bool isBuiltinPath(const CscStr &path){ 
    return indexOfBuiltinPath(path) != -1;
}

CSC_END
#endif