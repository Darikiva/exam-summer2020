#include <iostream>
#include <trees/splay_set.hpp>

void fukc(exam::trees::SplaySet<int> &t, int val) {
    if (t.exist(val) != t.end()) {
        std::cout<<"Exists"<<std::endl;
    } else {
        std::cout<<"Doesn't"<<std::endl;
    }
}

int main() {
    exam::trees::SplaySet<int> t1;
    exam::trees::SplaySet<int> t2;
    t1.insert(10);
    t2.insert(42);
    auto t3 = exam::trees::unite(t1, t2);
    fukc(t3, 42);
    fukc(t3, 10);

    
    return 0;
}
