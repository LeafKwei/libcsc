#ifndef DBC_HANDLER_HPP
#define DBC_HANDLER_HPP

#include <string>
#include "dbc.hpp"
#include "alias.hpp"
#include "DbcEflag.hpp"
#include "DbcEditor.hpp"

DBC_BEGIN

class DbcHandler{
public:
    DbcHandler();
    DbcHandler(const DbcString &raw);
    DbcHandler(const DbcHandler &oth);
    DbcHandler(DbcHandler &&oth) noexcept;
    ~DbcHandler();

    DbcEflag   decode(const DbcString &raw) noexcept;
    DbcValue  find(DbcKey key) noexcept;
    DbcEditor editor() noexcept;
    DbcEflag   clear() noexcept;
    DbcString  encode() noexcept;

private:
};

DBC_END
#endif