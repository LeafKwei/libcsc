#include "csc/syntax/Keyseq.hpp"
CSC_BEGIN

Keyseq& Keyseq::start(const String &str){
    seq_.clear();
    seq_ = str;
    return *this;
}

Keyseq& Keyseq::append(const String &str){
    seq_.push_back('_');
    seq_.append(str);
    return *this;
}

Keyseq& Keyseq::clear(){
    seq_.clear();
    return *this;
}

bool Keyseq::empty() const noexcept{
    return seq_.empty();
}

const String& Keyseq::seq() const noexcept{
    return seq_;
}

CSC_END