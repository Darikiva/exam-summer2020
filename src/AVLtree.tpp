//
// Created by darik on 6/8/2020.
//

#include "AVLTree.hpp"

template<typename Item>
void AVLTree<Item>::_rotateLeft(shared_ptr<AVLNode<Item>> node) {
    auto right_sibling = node->_right;
    auto parent = node->_parent;
    if (parent) {
        bool is_right_son = (parent->_right == node);
        if (is_right_son) {
            parent->_right = right_sibling;
        } else {
            parent->_left = right_sibling;
        }
    } else {
        _root = right_sibling;
    }

    if (right_sibling->_left) {
        right_sibling->_left->_parent = node;
    }

    node->_right = right_sibling->_left;
    right_sibling->_left = node;
    node->_parent = right_sibling;
    right_sibling->_parent = parent;

    node->fixHeight();
    right_sibling->fixHeight();
}

template<typename Item>
void AVLTree<Item>::_rotateRight(shared_ptr<AVLNode<Item>> node) {
    auto left_sibling = node->_left;
    auto parent = node->_parent;

    if (parent) {
        bool is_right_son = (parent->_right == node);
        if (is_right_son) {
            parent->_right = left_sibling;
        } else {
            parent->_left = left_sibling;
        }
    } else {
        _root = left_sibling;
    }

    if (left_sibling->_right) {
        left_sibling->_right->_parent = node;
    }

    node->_left = left_sibling->_right;
    left_sibling->_right = node;
    node->_parent = left_sibling;
    left_sibling->_parent = parent;

    node->fixHeight();
    left_sibling->fixHeight();
}

template<typename Item>
void AVLTree<Item>::_bigRotateLeft(shared_ptr<AVLNode<Item>> node) {
    _rotateRight(node->_right);
    _rotateLeft(node);
}

template<typename Item>
void AVLTree<Item>::_bigRotateRight(shared_ptr<AVLNode<Item>> node) {
    _rotateLeft(node->_left);
    _rotateRight(node);
}

template<typename Item>
shared_ptr<AVLNode<Item>> AVLTree<Item>::search(Item key) {
    auto node = _root;
    while (node) {
        if (node->_key == key) return node;
        else if (key < node->_key) {
            node = node->_left;
        } else {
            node = node->_right;
        }
    }
    return nullptr;
}

template<typename Item>
void AVLTree<Item>::insert(Item key) {
    ++count;

    if (_root == nullptr) {
        _root = make_shared<AVLNode<Item>>(key, nullptr, nullptr, nullptr);
        return;
    }
    shared_ptr<AVLNode<Item>> node_for_insert = shared_ptr<AVLNode<Item>>(this->_root);
    for (;;) {
        if (key < node_for_insert->_key) {
            if (node_for_insert->_left) {
                node_for_insert = node_for_insert->_left;
            } else {
                node_for_insert->_left = make_shared<AVLNode<Item>>(key, nullptr, nullptr, node_for_insert);
                break;
            }
        } else {
            if (node_for_insert->_right) {
                node_for_insert = node_for_insert->_right;
            } else {
                node_for_insert->_right = make_shared<AVLNode<Item>>(key, nullptr, nullptr, node_for_insert);
                break;
            }
        }
    }

    while (node_for_insert) {
        node_for_insert->fixHeight();
        if (abs(node_for_insert->diff()) == 1) {
            node_for_insert = node_for_insert->_parent;
        } else if (node_for_insert->diff() == -2) {
            if (node_for_insert->_right->diff() == -1 || node_for_insert->_right->diff() == 0) {
                _rotateLeft(node_for_insert);
                return;
            } else if (node_for_insert->_right->diff() == 1) {
                _bigRotateLeft(node_for_insert);
            }
        } else if (node_for_insert->diff() == 2) {
            if (node_for_insert->_left->diff() == 1 || node_for_insert->_left->diff() == 0) {
                _rotateRight(node_for_insert);
                return;
            } else if (node_for_insert->_left->diff() == -1) {
                _bigRotateRight(node_for_insert);
            }
        } else if (node_for_insert->diff() == 0)
            return;
        else {
            node_for_insert = node_for_insert->_parent;
        }
    }
}

template<typename Item>
shared_ptr<AVLNode<Item>> AVLTree<Item>::_next(shared_ptr<AVLNode<Item>> node) {
    if (node->_right) {
        auto answer = node->_right;
        while (answer->_left) {
            answer = answer->_left;
        }
        return answer;
    } else if (node->_parent) {
        auto answer = node;
        while (answer->_parent && answer->_parent->_left != answer) {
            answer = answer->_parent;
        }
        if (answer->_parent) return answer->_parent;
        else return nullptr;
    } else {
        return nullptr;
    }
}

template<typename Item>
shared_ptr<AVLNode<Item>> AVLTree<Item>::_previous(shared_ptr<AVLNode<Item>> node) {
    if (node->_left) {
        auto answer = node->_left;
        while (answer->_right) {
            answer = answer->_right;
        }
        return answer;
    } else if (node->_parent) {
        auto answer = node;
        while (answer->_parent && answer->_parent->_right != answer) {
            answer = answer->_parent;
        }
        if (answer->_parent) return answer->_parent;
        else return nullptr;
    } else {
        return nullptr;
    }
}

template<typename Item>
void AVLTree<Item>::remove(Item key) {
    auto node = search(key);
    if (!node) return;
    --count;
    if (!node->_left && !node->_right) {
        if (node->_parent) {
            if (node->_parent->_left == node) {
                node->_parent->_left = nullptr;
            } else {
                node->_parent->_right = nullptr;
            }
            node = node->_parent;
            while (node) {
                node->fixHeight();
                if (abs(node->diff()) == 1) return;
                else if (node->diff() == -2) {
                    if (node->_right->diff() == -1 || node->_right->diff() == 0) {
                        _rotateLeft(node);
                        return;
                    } else if (node->_right->diff() == 1) {
                        _bigRotateLeft(node);
                    }
                } else if (node->diff() == 2) {
                    if (node->_left->diff() == 1 || node->_left->diff() == 0) {
                        _rotateRight(node);
                        return;
                    } else if (node->_left->diff() == -1) {
                        _bigRotateRight(node);
                    }
                } else if (node->diff() == 0) {
                    node = node->_parent;
                }
            }
        } else {
            _root = nullptr;
        }
    } else {
        shared_ptr<AVLNode<Item>> nearest;
        if (node->_left) nearest = _previous(node);
        else nearest = _next(node);


        if (nearest->_parent->_left == nearest) {
            nearest->_parent->_left = nullptr;
        } else {
            nearest->_parent->_right = nullptr;
        }

        if (node->_parent) {
            if (node->_parent->_right == node) {
                node->_parent->_right = nearest;
            } else {
                node->_parent->_left = nearest;
            }
        }

        if (node->_left) {
            node->_left->_parent = nearest;
        }
        if (node->_right) {
            node->_right->_parent = nearest;
        }
        nearest->_parent = node->_parent;
        nearest->_left = node->_left;
        nearest->_right = node->_right;

        if (node == _root) _root = nearest;

        while (nearest) {
            nearest->fixHeight();
            if (abs(nearest->diff()) == 1) return;
            else if (nearest->diff() == -2) {
                if (nearest->_right->diff() == -1 || nearest->_right->diff() == 0) {
                    _rotateLeft(nearest);
                    return;
                } else if (nearest->_right->diff() == 1) {
                    _bigRotateLeft(nearest);
                }
            } else if (nearest->diff() == 2) {
                if (nearest->_left->diff() == 1 || nearest->_left->diff() == 0) {
                    _rotateRight(nearest);
                    return;
                } else if (nearest->_left->diff() == 1) {
                    _bigRotateRight(nearest);
                }
            } else if (nearest->diff() == 0) {
                nearest = nearest->_parent;
            }
        }
    }
}