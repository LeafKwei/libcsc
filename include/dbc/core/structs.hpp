#ifndef DBC_CORE_STRUCTS_HPP
#define DBC_CORE_STRUCTS_HPP

#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

struct Dpair;
struct Ddomain;
using DpairPtr = std::shared_ptr<Dpair>;
using DdomainPtr = std::shared_ptr<Ddomain>;

/*
struct Dpair{
    Dstring name;
    Dstring value;
    DpairPtr next;
    DpairPtr prev;
};

struct Ddomain{
    Dstring name;
    DpairPtr pairs;
    DdomainPtr parent;
    DdomainPtr child;
    DdomainPtr next;
    DdomainPtr prev;
};
*/
struct Dpair{
    Dstring name;
    Dstring value;
    DpairPtr next;
    DpairPtr prev;

    Dpair(){
        std::cout << "Pair Ctor" << std::endl;
    }

    ~Dpair(){
        std::cout << "Pair Dctor" << std::endl;
    }
};

struct Ddomain{
    Dstring name;
    DpairPtr pairs;
    DdomainPtr parent;
    DdomainPtr child;
    DdomainPtr next;
    DdomainPtr prev;

    Ddomain(){
        std::cout << "Domain Ctor" << std::endl;
    }

    ~Ddomain(){
        std::cout << "Domain Dctor" << std::endl;
    }
};

DBC_END
#endif