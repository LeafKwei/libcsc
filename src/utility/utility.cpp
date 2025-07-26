#include "dbc/utility/utility.hpp"
#include <algorithm>

DBC_BEGIN

Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters){
    Dstring result;

    for(int idx = 0; idx < elements.size(); idx++){
        auto &e = elements.at(idx);
        result = result + e;
        if(idx + 1 >= elements.size()) continue;                                             //Don't put splitor if 'e' is last element.
        if(std::find(filters.begin(), filters.end(), e) != filters.end()) continue;   //Don't put splitor if 'e' is in filter.
        result = result + splitor;
    }

    return result;
}

DBC_END