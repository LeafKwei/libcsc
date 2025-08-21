#ifndef DBC_CONFIG_HPP
#define DBC_CONFIG_HPP

#include "dbc/dbc.hpp"
#include "dbc/core/Ditem.hpp"
#include "dbc/context/Context.hpp"
#include "dbc/syntax/CommandDrv.hpp"
DBC_BEGIN

class Dconfig{
public:
    Dconfig() =default;

    void parse(const Dstring &str);
    Dstring toString();

private:
    Context m_context;
    CommandDrv m_driver;
};

DBC_END
#endif