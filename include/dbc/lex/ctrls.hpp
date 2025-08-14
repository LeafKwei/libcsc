#ifndef DBC_LEX_CTRLS_HPP
#define DBC_LEX_CTRLS_HPP

#include "dbc/lex/KeywordCtrl.hpp"
DBC_BEGIN

class TrueCtrl : public KeywordCtrl{
public:
    Dstring keyword() override;
    void changeReaderRule(ReaderBranches &readers) override;
};

class FalseCtrl : public KeywordCtrl{
public:
    Dstring keyword() override;
    void changeReaderRule(ReaderBranches &readers) override;
};

DBC_END
#endif