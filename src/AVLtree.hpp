//
// Created by darik on 6/8/2020.
//

#ifndef EXAM_SUMMER2020_AVLTREE_HPP
#define EXAM_SUMMER2020_AVLTREE_HPP

#include <memory>
#include <iostream>

using std::shared_ptr;
using std::make_shared;

template<typename Item>
class AVLNode {
public:
    Item _key;
    shared_ptr<AVLNode> _left;
    shared_ptr<AVLNode> _right;
    shared_ptr<AVLNode> _parent;
    int _height{1};

    explicit AVLNode<Item>(Item key, shared_ptr<AVLNode> left = nullptr, shared_ptr<AVLNode> right = nullptr,
                           shared_ptr<AVLNode> parent = nullptr)
            : _key{key}, _left{left}, _right{right}, _parent{parent} {}

    void fixHeight() {
        int left_height{0}, right_height{0};
        if (_left) left_height = _left->_height;
        if (_right) right_height = _right->_height;
        _height = std::max(left_height, right_height) + 1;
    }

    int diff() {
        int left_height{0}, right_height{0};
        if (_left) left_height = _left->_height;
        if (_right) right_height = _right->_height;
        return left_height - right_height;
    }
};

template<typename Item>
class AVLTree {
    class Iterator {
    private:
        shared_ptr<AVLNode<Item>> current_node;
        int current_position;
    public:
        Iterator(shared_ptr<AVLNode<Item>> node, int current_position) : current_node{node},
                                                                         current_position{current_position} {}

        Iterator &operator++() {
            current_node = _next(current_node);
            ++current_position;
        }

        bool operator!=(const Iterator &other) {

            return !(other.current_node == current_node && other.current_position == current_position);
        }

        Item operator*() {
            return current_node->_key;
        }
    };

public:
    shared_ptr<AVLNode<Item>> search(Item);

    void insert(Item);

    void remove(Item);

    std::string print() {
        return print(_root);
    };

    Iterator begin() {
        auto answer = _root;
        if (!answer) return Iterator(nullptr, 0);
        while (answer->_left) {
            answer = answer->_left;
        }
        return Iterator(answer, 1);
    }

    Iterator end() {
        return Iterator(nullptr, count + 1);
    }

private:
    shared_ptr<AVLNode<Item>> _root;

    int count{0};

    void _rotateLeft(shared_ptr<AVLNode<Item>>);

    void _bigRotateLeft(shared_ptr<AVLNode<Item>>);

    void _rotateRight(shared_ptr<AVLNode<Item>>);

    void _bigRotateRight(shared_ptr<AVLNode<Item>>);

    static shared_ptr<AVLNode<Item>> _next(shared_ptr<AVLNode<Item>> node);

    static shared_ptr<AVLNode<Item>> _previous(shared_ptr<AVLNode<Item>> node);

    std::string print(shared_ptr<AVLNode<Item>> node) {
        if (node == nullptr)
            return "";
        std::string answer;
        answer += std::to_string(node->_key);
        if (node->_left || node->_right) answer += "(";
        answer += print(node->_left);
        if (node->_left && node->_right) answer += ",";
        answer += print(node->_right);
        if (node->_left || node->_right) answer += ")";
        return answer;
    }
};

#include "AVLTree.tpp"

#endif //EXAM_SUMMER2020_AVLTREE_HPP
