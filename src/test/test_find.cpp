#include <iostream>
#include <vector>
#include "dbc/core/structs.hpp"

using dbc::Dscope;
using dbc::DscopePtr;
using dbc::Dstring;

DscopePtr findScopeFrom(const DscopePtr &begin, const std::vector<Dstring> &names, int pos) noexcept{
    auto nextptr = begin;

    while(nextptr != nullptr){
        if(nextptr -> name == names.at(pos)){
            if(pos + 1 == names.size()) return nextptr;
            return findScopeFrom(nextptr -> child, names, pos + 1);
        }

        nextptr = nextptr -> next;
    }

    return DscopePtr(nullptr);
}

void make_next(DscopePtr ptr, int n){
    auto p = ptr;
    
    for(int i = 0; i < n; i++){
        Dstring name;
        name.push_back(static_cast<char>('A' + i));
        p -> next = std::make_shared<Dscope>();
        p -> next -> name = name;
        p = p -> next;
    }
}

void show_all(const DscopePtr &ptr, int ind=0){
    auto begin = ptr;

    while(begin != nullptr){
        for(int i = 0; i < ind; i++) std::cout << " ";
        std::cout << begin -> name << std::endl;
        begin = begin -> next;
    }

    begin = ptr;
    while(begin != nullptr){
        show_all(begin -> child, ind + 1);
        begin = begin -> next;
    }
}

int main(void){
    DscopePtr root = std::make_shared<Dscope>();
    DscopePtr rchild = std::make_shared<Dscope>();
    root -> name = "/";
    root -> child = rchild;
    rchild -> name = "R";

    make_next(root -> child, 5);

    auto node1 = root -> child -> next -> next;
    DscopePtr n1child = std::make_shared<Dscope>();
    n1child -> name = "L";
    node1 -> child = n1child;

    make_next(node1 -> child, 5);

    if(findScopeFrom(root -> child, {"B", "E"}, 0) != nullptr){
        std::cout << "Found" << std::endl;
    }

    show_all(root);
}