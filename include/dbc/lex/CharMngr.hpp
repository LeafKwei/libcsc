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
    Dchar tryPick() const noexcept override; 
    void forward(unsigned int value=1) noexcept override;
    void backward(unsigned int value=1) noexcept override;
    bool hasMore() const noexcept override;
    int count() noexcept override;
    CharsOptor charsoptor() const noexcept override; 
    
private:
    Dstring m_raw;
    bool m_indexFlag;
    int m_index;
    int m_count;
    int m_colNumber;
    int m_rowNumber;

    void updateCounter(unsigned int value=1) noexcept;
};


DBC_END
#endif