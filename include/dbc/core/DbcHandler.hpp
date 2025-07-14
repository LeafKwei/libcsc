#ifndef DBC_HANDLER_HPP
#define DBC_HANDLER_HPP

#include <string>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
DBC_BEGIN

class DbcHandler{
public:
    DbcHandler();
    DbcHandler(const DbcString &raw);
    DbcHandler(const DbcHandler &oth);
    DbcHandler(DbcHandler &&oth) noexcept;
    ~DbcHandler();

    DbcError  decode(const DbcString &raw) noexcept;  //An empty string indicate no error, otherwise the error message store into string
    void   find(DbcKey key) noexcept;
    void  editor() noexcept;
    DbcError  clear() noexcept;                                          //An empty string indicate no error, otherwise the error message store into string
    DbcString  encode() noexcept;

private:
};

DBC_END
#endif