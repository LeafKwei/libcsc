#ifndef DBC_CHARMNGR_HPP
#define DBC_CHARMNGR_HPP

#include "dbc/lex/CharPicker.hpp"
DBC_BEGIN

class CharMngr : CharPicker{
public:
    CharMngr(const Dstring &raw);
    Dchar pick() noexcept override;
    Dchar tryPick() noexcept override; 
    void forward(int value=1) noexcept override;
    void backward(int value=1) noexcept override;
    bool hasMore() const noexcept override;
    void setIndexFlag(bool flag) noexcept override;
private:
    Dstring m_raw;
};


DBC_END
#endif