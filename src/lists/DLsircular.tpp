//
// Created by darik on 6/8/2020.
//

#include "DLsircular.hpp"

template<typename Item>
void DLsircular<Item>::add(Item value) {
    if (start == nullptr) {
        start = std::make_shared<Node>(value);
        start->_prev = start;
        start->_next = start;
    } else {
        auto end = start->_prev;
        end->_next = std::make_shared<Node>(value, end, start);
        start->_prev = end->_next;
    }
    ++size;
}

template<typename Item>
void DLsircular<Item>::remove(int index) {
    if (start == nullptr) return;
    --size;
    if (start->_next == start) {
        start = nullptr;
        return;
    }
    auto node = start;
    while (index != 0) {
        --index;
        node = node->_next;
    }
    node->_prev->_next = node->_next;
    node->_next->_prev = node->_prev;
    if (node == start) {
        start = start->_next;
    }
}
