#include <iostream>
#include <trees/splay_set.hpp>
#include "lists/DLsircular.hpp"

void fukc(exam::trees::SplaySet<int> &t, int val) {
    if (t.exist(val) != t.end()) {
        std::cout<<"Exists"<<std::endl;
    } else {
        std::cout<<"Doesn't"<<std::endl;
    }
}

int main() {
    DLsircular<int> list;
    for(int i = 0; i < 10; ++i)
        list.add(i);

    for(auto i:list) std::cout << i << " ";
    for(int i = 0; i < 10; ++i){
        list.remove(0);
        for(auto j:list) std::cout << j << " ";
        std::cout << std::endl;
    }
    return 0;
}
