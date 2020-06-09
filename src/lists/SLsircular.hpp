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
            int count;
            const SLsircular* list;
        public:
            Iterator(std::shared_ptr<Node> current, int count, const SLsircular* list) :
                    current{current}, count{count}, list{list} {};


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
                if (count == 0) count = list->getSize();
                auto tmp = current;
                while(current->_next != tmp) current = current->_next;
                --count;
                return *this;
            }

            Iterator &operator++() {
                if (count == list->getSize()) count = 0;
                current = current->_next;
                ++count;
                return *this;
            }

            int getCount() const {
                return count;
            }
        };

    public:
        SLsircular() : start{nullptr}, size{0} {};

        void add(Item value);

        void removeByIndex(int index);

        void removeByValue(Item value);

        std::shared_ptr<Node> getStart() const {
            return start;
        }

//
        Iterator begin() {
            return Iterator(this->start, 0, this);
        }

//
        Iterator end() {
            return Iterator(this->start, size, this);
        }

        Iterator search(Item _value) {
            for (auto it = begin(); it < end(); ++it) {
                if (*it == _value) return it;
            }
            return end();
        };

        Iterator searchByValue(Item _value) {
            for (auto it = begin(); it < end(); ++it) {
                if (*it == _value) return it;
            }
            return end();
        };

        Iterator searchByIndex(int index) {
            auto tmp = start;
            int count;
            while(index != 0) {
                tmp = tmp->_next;
                --index;
                ++count;
                if(count == this->size) count = 0;
            }
            return Iterator(tmp, count, this);
        }

        int getSize() const {
            return size;
        }
    private:
        std::shared_ptr<Node> start;
        int size;
    };
}


#include "SLsircular.tpp"