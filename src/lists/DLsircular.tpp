//
// Created by darik on 6/8/2020.
//

#include "DLsircular.hpp"

namespace exam::lists {
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
    void DLsircular<Item>::removeByIndex(int index) {
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

    template<typename Item>
    void DLsircular<Item>::removeByValue(Item value) {
        if(start->_value == value) {
            removeByIndex(0);
            return;
        }
        auto tmp = start;
        int index = 0;
        while(tmp->_next != start) {
            if(tmp->_value == value) {
                removeByIndex(index);
                return;
            } else {
                index++;
                tmp = tmp->_next;
            }
        }
    }
}