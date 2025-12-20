#include "csc/syntax/Keyseq.hpp"
CSC_BEGIN

Keyseq& Keyseq::start(const String &str){
    seq_.clear();
    seq_ = str;
}

Keyseq& Keyseq::append(const String &str){
    seq_.push_back('_');
    seq_ = seq_.append(str);
}

Keyseq& Keyseq::clear(){
    seq_.clear();
}

bool Keyseq::empty() const noexcept{
    return seq_.empty();
}

const String& Keyseq::seq() const noexcept{
    return seq_;
}

CSC_END