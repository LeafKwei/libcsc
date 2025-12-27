#ifndef CSC_MAPSCOPE_HPP
#define CSC_MAPSCOPE_HPP

#include <map>
#include "csc/context/Scope.hpp"
CSC_BEGIN

class MapScope : public Scope{
public:
    using VariableMap = std::map<String, VariablePtr>;

public:
    MapScope(const String &name, UID id);
    bool           insertVariable(const String &name, VariablePtr vp) override;
    VariablePtr findVariable(const String &name) override;
    VariablePtr variable(int index) override;
    Size_t          size() const noexcept override;
    String          name() const noexcept override;
    UID             id() const noexcept override;

private:
    UID                    id_;
    String                name_;
    VariableMap     variables_;
};

CSC_END
#endif