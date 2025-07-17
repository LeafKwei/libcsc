#ifndef DBC_HANDLER_HPP
#define DBC_HANDLER_HPP

#include <string>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
DBC_BEGIN

class Dhandler{
public:
    Dhandler();
    Dhandler(const Dstring &raw);
    Dhandler(const Dhandler &oth);
    Dhandler(Dhandler &&oth) noexcept;
    ~Dhandler();

    Derror  decode(const Dstring &raw) noexcept;  //An empty string indicate no error, otherwise the error message store into string
    Dstring  encode() noexcept;

private:
};

DBC_END
#endif