#ifndef DBC_AUXI_HPP
#define DBC_AUXI_HPP

#include <vector>
#include <tuple>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"

DBC_BEGIN

std::tuple<Dstring,Dstring> separate(const Dstring &path) noexcept;
std::vector<Dstring> splitPath(const Dstring &path) noexcept;

DBC_END
#endif