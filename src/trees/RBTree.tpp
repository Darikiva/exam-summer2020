#include"RBTree.hpp"
#include <cassert>

namespace exam::trees {

    template<typename T>
    RBTree<T>::Iterator::Iterator():_node(nullptr){}

    template<typename T>
    RBTree<T>::Iterator::Iterator(typename RBTree<T>::Node* node) : _node(node) {}

    template<typename T>
    const T& RBTree<T>::Iterator::operator*() const noexcept {
        assert(_node && "Iterator for nullptr doesn't have data");
        return (_node->key);
    }

    template<typename T>
    bool RBTree<T>::Iterator::empty() const noexcept { return _node == nullptr; }

    template<typename T>
    bool RBTree<T>::Iterator::operator!=(const Iterator &other) noexcept {
        return _node != other._node;
    }

    template<typename T>
    bool RBTree<T>::Iterator::operator==(const Iterator &other) noexcept {
        return _node == other._node;
    }
    
    template<typename T>
    typename RBTree<T>::Node* RBTree<T>::Node::next() {
        Node* node = this;
        if (node->right) {
            auto answer = node->right;
            while (answer->left && answer->left!=TNILL) {
                answer = answer->left;
            }
            return answer;
        }
        else if (node->parent && node->parent!=TNILL) {
            auto answer = node;
            while (answer->parent && answer->parent!=TNILL && answer->parent->left != answer) {
                answer = answer->parent;
            }
            if (answer->parent && answer->parent != TNILL) return answer->parent;
            else return nullptr;
        }
        else {
            return nullptr;
        }
    }

    template<typename T>
    typename RBTree<T>::Iterator& RBTree<T>::Iterator::operator++() noexcept {
        _node = _node->next();
        return *this;
    }

    template<typename T>
    RBTree<T>::RBTree() {
        TNILL = new Node;
        _root = TNILL;
    }

    template<typename T>
    RBTree<T>::Node::Node(T& _key) :parent(nullptr), key(_key), color(Color::red) {
        left = RBTree<T>::TNILL;
        right = RBTree<T>::TNILL;
    }

    template<typename T>
    void RBTree<T>::insert(T& key) {
        Node* node = new Node(key);
        if (_root == TNILL) {
            _root = node;
            return;
        }

        Node* y = nullptr;
        Node* x = _root;

        ///Searching for node's place
        while (x != TNILL) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            }
            else {
                x = x->right;
            }
        }

        ///node's parent needs to know that he has a new child!
        node->parent = y;
        if (y == nullptr) {
            _root = node;
        }
        else if (node->key < y->key) {
            y->left = node;
        }
        else {
            y->right = node;
        }

        ///node is a root node, nothing to do here
        if (node->parent == nullptr) {
            node->color = Node::Color::black;
            return;
        }

        ///if grandparent is nullptr, nothing to do here
        if (node->parent->parent == nullptr) {
            return;
        }

        _insertFixup(node);
    }

    template<typename T>
    void RBTree<T>::erase(const T& key) {
        Node* p = _search(_root, key);
        if (p)
            _delete(p);
    }

    template<typename T>
    typename RBTree<T>::Iterator RBTree<T>::search(const T& key) {
        Node* p = _search(_root, key);
        return Iterator(p);
    }

    template<typename T>
    typename RBTree<T>::Node* RBTree<T>::_search(Node* start, const T& key) {
        Node* x = start;
        while (x != TNILL)
            if (x->key == key)
                return x;
            else if (key < x->key)
                x = x->left;
            else
                x = x->right;
        return nullptr;
    }

    template<typename T>
    void RBTree<T>::_transplant(Node* oldNode, Node* newNode) {
        if (oldNode->parent == nullptr) {
            _root = newNode;
        }
        else if (oldNode == oldNode->parent->left) {
            oldNode->parent->left = newNode;
        }
        else {
            oldNode->parent->right = newNode;
        }

        newNode->parent = oldNode->parent;
    }

    template<typename T>
    typename RBTree<T>::Node* RBTree<T>::_min(Node* start) {
        while (start->left != TNILL)
            start = start->left;
        return start;
    }

    template<typename T>
    void RBTree<T>::_leftRotate(Node* target) {
        Node* futureParent = target->right;
        futureParent->parent = target->parent;
        if (target->parent && target->parent != TNILL)
        {
            if (target->parent->left == target)
                target->parent->left = futureParent;
            else
                target->parent->right = futureParent;
        }
        else
            _root = futureParent;

        target->parent = futureParent;
        target->right = futureParent->left;
        if (futureParent->left != TNILL)
            futureParent->left->parent = target;

        futureParent->left = target;
    }

    template<typename T>
    void RBTree<T>::_rightRotate(Node* target) {
        Node* futureParent = target->left;
        futureParent->parent = target->parent;
        if (target->parent && target->parent != TNILL)
        {
            if (target->parent->right == target)
                target->parent->right = futureParent;
            else
                target->parent->left = futureParent;
        }
        else
            _root = futureParent;
        target->parent = futureParent;
        target->left = futureParent->right;
        if (futureParent->right != TNILL)
            futureParent->right->parent = target;

        futureParent->right = target;
    }

    template<typename T>
    void RBTree<T>::_insertFixup(Node* node) {
        Node* u;
        while (node->parent->color == Node::Color::red) {
            if (node->parent == node->parent->parent->right) {
                u = node->parent->parent->left;
                if (u->color == Node::Color::red) {
                    u->color = Node::Color::black;
                    node->parent->color = Node::Color::black;
                    node->parent->parent->color = Node::Color::red;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        _rightRotate(node);
                    }
                    node->parent->color = Node::Color::black;
                    node->parent->parent->color = Node::Color::red;
                    _leftRotate(node->parent->parent);
                }
            }
            else {
                u = node->parent->parent->right;

                if (u->color == Node::Color::red) {
                    u->color = Node::Color::black;
                    node->parent->color = Node::Color::black;
                    node->parent->parent->color = Node::Color::red;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        _leftRotate(node);
                    }
                    node->parent->color = Node::Color::black;
                    node->parent->parent->color = Node::Color::red;
                    _rightRotate(node->parent->parent);
                }
            }
            if (node == _root) {
                break;
            }
        }
        _root->color = Node::Color::black;
    }

    template<typename T>
    void RBTree<T>::_deleteFixup(Node* node) {
        Node* s;
        while (node != _root
            && node->color == Node::Color::black)
        {
            if (node == node->parent->left) {
                s = node->parent->right;
                if (s->color == Node::Color::red) {
                    s->color = Node::Color::black;
                    node->parent->color = Node::Color::red;
                    _leftRotate(node->parent);
                    s = node->parent->right;
                }

                if (s->left->color == Node::Color::black
                    && s->right->color == Node::Color::black)
                {
                    s->color = Node::Color::red;
                    node = node->parent;
                }
                else {
                    if (s->right->color == Node::Color::black) {
                        s->left->color = Node::Color::black;
                        s->color = Node::Color::red;
                        _rightRotate(s);
                        s = node->parent->right;
                    }

                    s->color = node->parent->color;
                    node->parent->color = Node::Color::black;
                    s->right->color = Node::Color::black;
                    _leftRotate(node->parent);
                    node = _root;
                }
            }
            else {
                s = node->parent->left;
                if (s->color == Node::Color::red) {
                    s->color = Node::Color::black;
                    node->parent->color = Node::Color::red;
                    _rightRotate(node->parent);
                    s = node->parent->left;
                }

                if (s->right->color == Node::Color::black
                    && s->right->color == Node::Color::black)
                {
                    s->color = Node::Color::red;
                    node = node->parent;
                }
                else {
                    if (s->left->color == Node::Color::black) {
                        s->right->color = Node::Color::black;
                        s->color = Node::Color::red;
                        _leftRotate(s);
                        s = node->parent->left;
                    }
                    s->color = node->parent->color;
                    node->parent->color = Node::Color::black;
                    s->left->color = Node::Color::black;
                    _rightRotate(node->parent);
                    node = _root;
                }
            }
        }
        node->color = Node::Color::black;
    }

    template<typename T>
    void RBTree<T>::_delete(Node* z) {
        Node* y;
        Node* x;
        y = z;
        typename RBTree<T>::Node::Color ogColor = y->color;

        if (z->left == TNILL) {
            x = z->right;
            _transplant(z, z->right);
        }
        else if (z->right == TNILL) {
            x = z->left;
            _transplant(z, z->left);
        }
        else {
            y = _min(z->right);
            ogColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            }
            else {
                _transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            _transplant(z, y);

            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        z->left = z->right = nullptr;
        delete z;
        if (ogColor == Node::Color::black) {
            _deleteFixup(x);
        }
    }
}