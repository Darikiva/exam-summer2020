//
// Created by darik on 6/9/2020.
//

#include "SLsircular.hpp"

namespace exam::lists{
    template<typename Item>
    void SLsircular<Item>::add(Item value) {
        if (start == nullptr) {
            start = std::make_shared<Node>(value);
            start->_next = start;
        } else {
            auto tmp = start;
            while(tmp->_next != start) tmp = tmp->_next;
            tmp->_next = std::make_shared<Node>(value, start);
        }
        ++size;
    }

    template<typename Item>
    void SLsircular<Item>::removeByIndex(int index) {
        if (start == nullptr) return;
        --size;
        if (start->_next == start) {
            start = nullptr;
            return;
        }
        if (index == 0) {
            auto tmp = start;
            while(tmp->_next != start) tmp = tmp->_next;
            tmp->_next = start->_next;
            start = start->_next;
            return;
        }
        auto node = start;
        while (index != 1) {
            --index;
            node = node->_next;
        }
        node->_next = node->_next->_next;
    }

    template<typename Item>
    void SLsircular<Item>::removeByValue(Item value) {
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