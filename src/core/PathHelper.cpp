#include "cassert"
#include "csc/core/PathHelper.hpp"
CSC_BEGIN

PathHelper::PathHelper(crString path){
    classify(path);
}

bool PathHelper::valid() const noexcept{
    return m_valid;
}

bool PathHelper::isAbsolute() const noexcept{
    return m_absolute;
}

bool PathHelper::isRoot() const noexcept{
    return m_absolute && m_valid && m_items.size() == 0;
}

Size_t PathHelper::size() const noexcept{
    return m_items.size();
}

String PathHelper::buildPath(int endidx) const{
    String path = (m_absolute) ? "/" : "";   //根据原路径是否是绝对路径来决定是否添加根路径

    for(int i = 0; i < endidx; i++){
        path.append(m_items.at(i));
        path.push_back('/');                          //最后一次循环会多出一个分隔符，需要在返回前删除
    }

    if(endidx > 0) path.pop_back();          //删除末尾多余的分隔符，检查endix是为了确保仅存在/的时候不会将其误删
    return path;
}

crString PathHelper::item(int index) const{
    return m_items.at(index);
}

crString PathHelper::lastItem() const{
    assert(m_items.size() > 0);
    return m_items.at(m_items.size() - 1);
}

void PathHelper::classify(crString path){
    if(path.find('/') == 0){
        m_absolute = true;
        m_valid = splitPath(path, 1);        //index设置为1是为了跳过绝对路径的'/'
    }
    else{
        m_absolute = false;
        m_valid = splitPath(path, 0);
    }
}

bool PathHelper::splitPath(crString path, int index){
    Size_t idx = index;

    if(path == "/"){                         //对仅存在根路径的情况做特殊处理
        return true;
    }

    while(idx < path.size()){
        auto nidx = path.find('/', idx);
        if(nidx == path.npos){          //如果没有下一个分隔符'/'并且没有到达字符串末尾，则说明字符串剩余内容是一个item
            m_items.push_back(path.substr(idx));
            break;
        }

        /* 保存两个分隔符间的item，然后更新idx到下一个分隔符后的字符位置 */
        m_items.push_back(path.substr(idx, (nidx - idx)));
        idx = nidx + 1;
    }

    return m_items.size() > 0;
}

CSC_END