#pragma once

#include <memory>

namespace exam::list {

    template<typename Item>
    class SL {
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

            bool operator!=(const Iterator &other) {
                return other.count != this->count;
            }

            bool operator<(const Iterator &other) {
                return (this->count < other.count);
            }

            Iterator &operator--() {
                return nullptr;
            }

            Iterator &operator++() {
                current = current->_next;
                ++count;
                return *this;
            }
        };

    public:
        SL() : start{nullptr}, size{0} {};

        void add(Item value);

        void remove(int index);

        std::shared_ptr<Node> getStart() const {
            return start;
        }

        Iterator begin() {
            return Iterator(this->start, 0, size);
        }

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


    template<typename Item>
    void SL<Item>::add(Item value) {
        if (start == nullptr) {
            start = std::make_shared<Node>(value);
            start->_next = nullptr;
        } else {
            auto temp = start;
            while (temp->_next) {
                temp = temp->_next;
            }

            temp->_next = std::make_shared<Node>(value);
        }
        ++size;
    }

    template<typename Item>
    void SL<Item>::remove(int index) {
        if (start == nullptr) return;
        --size;
        if (start->_next == nullptr) {
            start = nullptr;
            return;
        }

        int count = 0;
        auto current = start;
        auto previous = current;
        while (count <= index) {
            if (count == index) {
                previous->_next = current->_next;
                current = nullptr;
            } else {
                previous = current;
                current = current->_next;
            }
            count++;
        }
    }
} // namespace exam
