#ifndef DBC_KEYWORDCTL_HPP
#define DBC_KEYWORDCTL_HPP

#include <map>
#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/lex/TokenReader.hpp"
DBC_BEGIN

class KeywordCtrl;
using CtrlPtr= std::shared_ptr<KeywordCtrl>;
using CtrlBranches = std::map<Dstring, CtrlPtr>;

class KeywordCtrl{
public:
    virtual Dstring keyword() =0;                                                        //Return keyword of this object represendted.
    virtual void changeReaderRule(ReaderBranches &readers) =0;   //Modify reades's rule properties.
};

DBC_END
#endif