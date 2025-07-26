#ifndef DBC_CHARMNGR_HPP
#define DBC_CHARMNGR_HPP

#include "dbc/lex/CharPicker.hpp"
DBC_BEGIN

class CharMngr : public CharPicker{
public:
    CharMngr(const Dstring &raw);

    int numberOfCol() const noexcept;
    int numberOfRow() const noexcept;

    Dchar pick() noexcept override;
    Dstring pickn(unsigned int n) noexcept override;
    Dchar tryPick() const noexcept override; 
    Dstring tryPickn(unsigned int n) const noexcept;
    void forward(unsigned int value=1) noexcept override;
    void backward(unsigned int value=1) noexcept override;
    bool hasMore() const noexcept override;
    
private:
    Dstring m_raw;
    bool m_indexFlag;
    int m_index;
    int m_colNumber;
    int m_rowNumber;
};


DBC_END
#endif