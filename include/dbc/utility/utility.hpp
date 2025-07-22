#ifndef DBC_AUXI_HPP
#define DBC_AUXI_HPP

#include <vector>
#include <tuple>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"

DBC_BEGIN

inline bool isEmptyPath(const Dstring &path) noexcept { return path.size() == 0; }
inline bool isBuiltinPath(const Dstring &path) noexcept { return path == "/"; }
Dstring join(Dstring splitor, const std::vector<Dstring> &elements, const std::initializer_list<Dstring> &filters={});
std::tuple<Dstring,Dstring> separate(const Dstring &path) noexcept;
std::vector<Dstring> splitPath(const Dstring &path) noexcept;

DBC_END
#endif