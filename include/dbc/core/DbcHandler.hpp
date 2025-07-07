#ifndef DBC_HANDLER_HPP
#define DBC_HANDLER_HPP

#include <string>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/core/DbcEflag.hpp"
#include "dbc/core/DbcEditor.hpp"

DBC_BEGIN

class DbcHandler{
public:
    DbcHandler();
    DbcHandler(const DbcString &raw);
    DbcHandler(const DbcHandler &oth);
    DbcHandler(DbcHandler &&oth) noexcept;
    ~DbcHandler();

    DbcString  decode(const DbcString &raw) noexcept;  //An empty string indicate no error, otherwise the error message store into string
    DbcValue   find(DbcKey key) noexcept;
    DbcEditor  editor() noexcept;
    DbcString  clear() noexcept;                                          //An empty string indicate no error, otherwise the error message store into string
    DbcString  encode() noexcept;

private:
};

DBC_END
#endif