//
// Created by darik on 6/8/2020.
//

#pragma once

#include <memory>

namespace exam::lists {
    template<typename Item>
    class DLsircular {
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
            int count;
            const DLsircular* list;
        public:
            Iterator(std::shared_ptr<Node> current, int count, const DLsircular* list) :
                    current{current}, count{count},  list{list} {};


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
                current = current->_prev;
                --count;
                return *this;
            }

            Iterator &operator++() {
                if (count == list->getSize()) count = 0;
                current = current->_next;
                ++count;
                return *this;
            }

            bool operator==(const Iterator& other) {
                return (this->count == other.count);
            }

            int getCount() const {
                return count;
            }
        };

    public:
        DLsircular() : start{nullptr}, size{0} {};

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
#include "DLsircular.tpp"
