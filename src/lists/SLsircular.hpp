//
// Created by darik on 6/9/2020.
//
#pragma once

#include <memory>

namespace exam::lists {
    template <typename Item>
    class SLsircular{
        class Node {
        public:
            Item _value;
            std::shared_ptr<Node> _next;

            explicit Node(Item value, std::shared_ptr<Node> next = nullptr) :
                    _value{value}, _next{next} {}
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
                if (count == 0) count = size;
                auto tmp = current;
                while(current->_next != tmp) current = current->_next;
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
        SLsircular() : start{nullptr}, size{0} {};

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

        Iterator search(Item _value) {
            for (auto it = begin(); it < end(); ++it) {
                if (*it == _value) return it;
            }
            return end();
        };

    private:
        std::shared_ptr<Node> start;
        int size;
    };
}


#include "SLsircular.tpp"