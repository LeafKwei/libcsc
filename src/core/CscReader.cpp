#include "csc/core/CscReader.hpp"
#include "csc/core/CscWalkerString.hpp"
CSC_BEGIN

CscReader::CscReader(Context &context) : context_(context){
    
}

bool CscReader::accessible(const String &path, bool v) const{
    PathHelper helper(path);
    if(!helper.valid()) return false;
    if(helper.rootonly()) return !(v);                                      //对于根路径'/'的特别处理，当参数v为true时，由于根目录不是变量，所以要返回false

    auto end = (helper.size() > 0) ? helper.size() - 1 : 0;      //仅遍历路径最后一个item之前的item
    auto looker = context_.looker(helper.absolute());

    /* 对于路径的前面部分，都视作scope名称检查 */
    for(Size_t i = 0; i < end; i++){
        looker.looksco(helper.element(i));
    }

    /* 如果路径部分已经出错，则直接返回 */
    if(!looker.done()){
        return false;
    }

    /* 最后一部分则根据参数v决定是作为scope名称还是variable名称检查 */
    return (v) 
        ? looker.lookvar(helper.basename()).done() 
        : looker.looksco(helper.basename()).done();
}

void CscReader::enter(const String &path) const{
    PathHelper helper(path);

    if(!helper.valid()) throw CscExcept("Invalid path: " + path);
    if(helper.absolute()){  //如果是根路径'/'，由于helper.size()为0，所以下方的循环不会执行
        context_.restart();   //因此通过这条语句既可以处理根路径，也可以处理绝对路径
    }

    for(Size_t idx = 0; idx < helper.size(); idx++){
        context_.enterScope(helper.element(idx));
    }
}

Walker CscReader::walker() const{
    return context_.walker();
}

String CscReader::toString() const{
    CscWalkerString cws(context_.walker(), context_.isRootScope());
    return cws.localstr();
}

CSC_END