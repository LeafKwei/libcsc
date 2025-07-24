#ifndef DBC_AUXI_HPP
#define DBC_AUXI_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"

DBC_BEGIN

Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters={});

DBC_END
#endif