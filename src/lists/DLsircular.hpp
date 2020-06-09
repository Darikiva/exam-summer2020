//
// Created by darik on 6/8/2020.
//

#pragma once

#include <memory>

template<typename Item>
class DLsircular{
    class Node {
    public:
        Item _value;
        std::shared_ptr<Node> _prev;
        std::shared_ptr<Node> _next;

        explicit Node(Item value, std::shared_ptr<Node> prev = nullptr, std::shared_ptr<Node> next = nullptr) :
                _value{value}, _prev{prev}, _next{next} {}
    };

    class Iterator {
    private:
        std::shared_ptr<Node> current;
        int size;
        int count;
    public:
        Iterator(std::shared_ptr<Node> current, int count, int size) :
                current{current}, count{count}, size{size} {};


        Item operator*() {
            return current->_value;
        }
//
        bool operator!=(const Iterator &other) {
            return !(other.count == this->count);
        }
//
        bool operator<(const Iterator &other) {
            return (this->count < other.count);
        }
        Iterator &operator--() {
            if(count == 0) count = size;
            current = current->_prev;
            --count;
            return *this;
        }

        Iterator &operator++() {
            if (count == size) count = 0;
            current = current->_next;
            ++count;
            return *this;
        }
    };
public:
    DLsircular() : start{nullptr}, size{0} {};

    void add(Item value);

    void remove(int index);

    std::shared_ptr<Node> getStart() const {
        return start;
    }
//
    Iterator begin() {
        return Iterator(this->start, 0, size);
    }
//
     Iterator end() {
        return Iterator(this->start, size, size);
    }

    Iterator search(Item _value){
        for(auto it = begin(); it < end(); ++it){
            if(*it == _value) return it;
        }
        return end();
    };

private:
    std::shared_ptr<Node> start;
    int size;
};

#include "DLsircular.tpp"
