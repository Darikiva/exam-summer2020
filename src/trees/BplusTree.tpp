#pragma once

#include "BplusTree.hpp"
#include <cassert>

namespace exam::trees {
    namespace {
        template<typename T>
        int firstGreater(const vector<T>& v, const int val) {
            for (int i = 0; i < v.size(); ++i)
                if (val < v[i])
                    return i;
            return v.size();
        }
    }

    template<typename T>
    BplusTree<T>::BplusTree(const int m) :M{ m }, MININD{ int(m / 2) - 1 ? int(m / 2) - 1 : 1 }, root(nullptr), minNode(nullptr) {
    }

    template<typename T>
    BplusTree<T>::~BplusTree() {
    }

    template<typename T>
    void BplusTree<T>::split(NodePtr ptr) {
        NodePtr newN = std::make_shared<BplusNode>();

        ///Split indexes
        std::copy(ptr->indexes.begin(), ptr->indexes.begin() + MININD, std::back_inserter(newN->indexes));
        ptr->indexes.erase(ptr->indexes.begin(), ptr->indexes.begin() + MININD);

        if (ptr->is_leaf()) {
            newN->prv = ptr->prv;
            ptr->prv->nxt = newN;
            newN->nxt = ptr;
            ptr->prv = newN;

            if (ptr == minNode)
                minNode = newN;

            ///Split data if leaves
            std::copy(ptr->data.begin(), ptr->data.begin() + MININD, std::back_inserter(newN->data));
            ptr->data.erase(ptr->data.begin(), ptr->data.begin() + MININD);
        }
        else {
            ///Split children if internal Nodes
            std::copy(ptr->children.begin(), ptr->children.begin() + MININD + 1, std::back_inserter(newN->children));
            for (int i = 0; i < newN->children.size(); ++i)
                newN->children[i]->parent = newN;
            ptr->children.erase(ptr->children.begin(), ptr->children.begin() + MININD + 1);
        }

        ///Maintain parent of new Node
        int spl = ptr->indexes[0];
        if (!ptr->is_leaf())
            ptr->indexes.erase(ptr->indexes.begin());
        NodePtr parent = ptr->parent;
        if (ptr == root) {
            parent = std::make_shared<BplusNode>();
            parent->indexes.push_back(spl);
            parent->children.push_back(newN);
            parent->children.push_back(ptr);
            ptr->parent = parent;
            root = parent;
        }
        else {
            int j = firstGreater(parent->indexes, spl);
            if (j != parent->indexes.size()) {
                parent->indexes.insert(parent->indexes.begin() + j, spl);
                parent->children.insert(parent->children.begin() + j, newN);
            }
            else {
                parent->indexes.push_back(spl);
                parent->children.insert(parent->children.begin() + parent->children.size() - 1, newN);
            }
        }

        newN->parent = ptr->parent;
    }

    template<typename T>
    void BplusTree<T>::borrowLeft(NodePtr ptr) {
        NodePtr br = ptr->left();
        ptr->indexes.insert(ptr->indexes.begin(), br->indexes[br->indexes.size() - 1]);
        br->indexes.erase(br->indexes.begin() + br->indexes.size() - 1);

        if (ptr->is_leaf()) {
            ptr->data.insert(ptr->data.begin(), br->data[br->data.size() - 1]);
            br->data.erase(br->data.begin() + br->data.size() - 1);

            int j = firstGreater(ptr->parent->indexes, ptr->indexes[0]);
            if (j == ptr->parent->indexes.size())
                j = ptr->parent->indexes.size() - 1;
            ptr->parent->indexes[j] = ptr->indexes[0];
        }
        else {
            ptr->children.insert(ptr->children.begin(), br->children[br->children.size() - 1]);
            br->children.erase(br->children.begin() + br->children.size() - 1);
            ptr->children[0]->parent = ptr;

            int j = firstGreater(ptr->parent->indexes, ptr->indexes[0]);
            if (j == ptr->parent->indexes.size())
                j = ptr->parent->indexes.size() - 1;
            std::swap(ptr->parent->indexes[j], ptr->indexes[0]);
        }
    }

    template<typename T>
    void BplusTree<T>::borrowRight(NodePtr ptr) {
        NodePtr br = ptr->right();
        ptr->indexes.push_back(br->indexes[0]);
        br->indexes.erase(br->indexes.begin());

        if (ptr->is_leaf()) {
            ptr->data.push_back(br->data[0]);
            br->data.erase(br->data.begin());

            int j = firstGreater(ptr->parent->indexes, br->indexes[0]);
            if (j == 0)
                j = 1;
            ptr->parent->indexes[j - 1] = br->indexes[0];
        }
        else {
            ptr->children.push_back(br->children[0]);
            br->children.erase(br->children.begin());
            ptr->children[ptr->children.size() - 1]->parent = ptr;

            int j = firstGreater(ptr->parent->indexes, br->indexes[0]);
            if (j == 0)
                j = 1;
            std::swap(ptr->parent->indexes[j - 1], ptr->indexes[ptr->indexes.size() - 1]);
        }
    }

    template<typename T>
    typename BplusTree<T>::NodePtr BplusTree<T>::merge(NodePtr ptr) const noexcept {
        NodePtr br;
        if (ptr->left()) {
            br = ptr->left();
        }
        else {
            br = ptr;
            ptr = ptr->right();
        }

        int os = br->indexes.size();
        br->indexes.resize(os + ptr->indexes.size());
        std::copy(ptr->indexes.begin(), ptr->indexes.end(), br->indexes.begin() + os);

        if (ptr->is_leaf()) {
            br->data.resize(os + ptr->data.size());
            std::copy(ptr->data.begin(), ptr->data.end(), br->data.begin() + os);
            br->nxt = ptr->nxt;
            ptr->nxt->prv = br;
        }
        else {
            br->children.resize(br->children.size() + ptr->children.size());
            std::copy(ptr->children.begin(), ptr->children.end(), br->children.begin() + br->children.size() - ptr->children.size());
            for (int i = br->children.size() - ptr->children.size(); i < br->children.size(); ++i)
                br->children[i]->parent = br;
        }

        int mark = os ? os - 1 : 0;
        int j = firstGreater(br->parent->indexes, br->indexes[mark]);
        if (j == br->parent->indexes.size())
            j = br->parent->indexes.size() - 1;

        if (!br->is_leaf())
            br->indexes.insert(br->indexes.begin() + os, br->parent->indexes[j]);

        br->parent->indexes.erase(br->parent->indexes.begin() + j);
        br->parent->children.erase(br->parent->children.begin() + j + 1);

        return br;
    }

    template<typename T>
    void BplusTree<T>::shrink() {
        NodePtr ch1 = root->children[0];
        NodePtr ch2 = root->children[1];
        root->children.clear();

        if (ch1->is_leaf()) {
            root->indexes.clear();
            root->indexes.resize(ch1->indexes.size() + ch2->indexes.size());
            std::copy(ch1->indexes.begin(), ch1->indexes.end(), root->indexes.begin());
            std::copy(ch2->indexes.begin(), ch2->indexes.end(), root->indexes.begin() + ch1->indexes.size());

            root->data.resize(ch1->data.size() + ch2->data.size());
            std::copy(ch1->data.begin(), ch1->data.end(), root->data.begin());
            std::copy(ch2->data.begin(), ch2->data.end(), root->data.begin() + ch1->data.size());

            root->nxt = root;
            root->prv = root;
            minNode = root;
        }
        else {
            int rootInd = root->indexes[0];
            root->indexes.resize(ch1->indexes.size() + 1 + ch2->indexes.size());
            std::copy(ch1->indexes.begin(), ch1->indexes.end(), root->indexes.begin());
            root->indexes[ch1->indexes.size()] = rootInd;
            std::copy(ch2->indexes.begin(), ch2->indexes.end(), root->indexes.begin() + ch1->indexes.size() + 1);

            root->children.resize(ch1->children.size() + ch2->children.size());
            std::copy(ch1->children.begin(), ch1->children.end(), root->children.begin());
            std::copy(ch2->children.begin(), ch2->children.end(), root->children.begin() + ch1->children.size());
            for (int i = 0; i < root->children.size(); ++i)
                root->children[i]->parent = root;
        }
    }

    template<typename T>
    void BplusTree<T>::insert(const int ind, const T& key) {
        if (root) {
            ///find leaf to insert
            NodePtr ptr = root;
            while (!ptr->is_leaf()) {
                int j = firstGreater(ptr->indexes, ind);
                ptr = ptr->children[j];
            }

            ///Insert new value into the leaf
            int j = firstGreater(ptr->indexes, ind);
            if (j != ptr->indexes.size()) {
                ptr->indexes.insert(ptr->indexes.begin() + j, ind);
                ptr->data.insert(ptr->data.begin() + j, key);
            }
            else {
                ptr->indexes.push_back(ind);
                ptr->data.push_back(key);
            }

            ///Leaf is full, splitting is needed
            if (ptr->indexes.size() == M) {
                while (ptr->indexes.size() == M) {
                    split(ptr);
                    ptr = ptr->parent;
                }
            }
        }
        ///Tree was empty, inserting the first value
        else {
            root = std::make_shared<BplusNode>();
            root->indexes.push_back(ind);
            root->data.push_back(key);
            root->nxt = root;
            root->prv = root;
            minNode = root;
        }
    }

    template<typename T>
    int BplusTree<T>::_min(NodePtr start) const {
        NodePtr ptr = start;
        while (!ptr->is_leaf())
            ptr = ptr->children[0];
        return ptr->indexes[0];
    }

    template<typename T>
    typename BplusTree<T>::NodePtr BplusTree<T>::BplusNode::left() const noexcept {
        if (parent)
            for (int i = 1; i < parent->children.size(); ++i)
                if (parent->children[i].get() == this)
                    return parent->children[i - 1];
        return nullptr;
    }

    template<typename T>
    typename BplusTree<T>::NodePtr BplusTree<T>::BplusNode::right() const noexcept {
        if (parent)
            for (int i = 0; i < parent->children.size() - 1; ++i)
                if (parent->children[i].get() == this)
                    return parent->children[i + 1];
        return nullptr;
    }

    template<typename T>
    void BplusTree<T>::remove(const int ind) {
        NodePtr ptr = root;
        int pos = -1;
        while (!ptr->is_leaf()) {
            int j = firstGreater(ptr->indexes, ind);
            ptr = ptr->children[j];
        }
        for (int i = 0; i < ptr->indexes.size(); ++i) {
            if (ptr->indexes[i] == ind) {
                pos = i;
            }
        }

        if (pos == -1)
            ptr = nullptr;

        if (ptr) {
            bool mult = false;
            int ind = ptr->indexes[pos];
            if ((pos != ptr->indexes.size() - 1) && (ptr->indexes[pos + 1] == ind))
                mult = true;
            ptr->indexes.erase(ptr->indexes.begin() + pos);
            ptr->data.erase(ptr->data.begin() + pos);

            if (ptr == root) {
                if (root->indexes.size() == 0)
                    root = nullptr;
                return;
            }

            if (ptr->indexes.size() < MININD) {
                while (true) {
                    ///Borrow from left brother
                    if ((ptr->left()) && (ptr->left()->indexes.size() > MININD)) {
                        borrowLeft(ptr);
                        break;
                    }
                    ///Borrow from right brother
                    else if ((ptr->right()) && (ptr->right()->indexes.size() > MININD)) {
                        borrowRight(ptr);
                        break;
                    }
                    ///Otherwise we can merge with brother and reduce the size of parent
                    else if ((ptr->parent != root) || ((ptr->parent == root) && (root->indexes.size() > 1))) {
                        ptr = merge(ptr);
                        if ((ptr->parent != root) && (ptr->parent->indexes.size() < MININD))
                            ptr = ptr->parent;
                        else
                            break;
                    }
                    ///If nothing helped, reducing the height is needed
                    else break;
                }

                ///Shrink the tree
                if (ptr->indexes.size() < MININD) {
                    shrink();
                }
            }

            ///Fix predecessors
            if (!mult) {
                ptr = ptr->parent;
                while (ptr) {
                    for (int i = 0; i < ptr->indexes.size(); ++i)
                        if (ptr->indexes[i] == ind)
                            ptr->indexes[i] = _min(ptr->children[i + 1]);
                    ptr = ptr->parent;
                }
            }
        }
    }

    template<typename T>
    typename BplusTree<T>::Iterator BplusTree<T>::search(const T& val) {
        NodePtr ptr = minNode;
        while (ptr) {
            for (int i = 0; i < ptr->data.size(); ++i)
                if (ptr->data[i] == val)
                    return Iterator(ptr, i);
            ptr = ptr->next();
        }
        return Iterator(nullptr);
    }

    template<typename T>
    BplusTree<T>::Iterator::Iterator(
        std::shared_ptr<typename BplusTree<T>::BplusNode> node,
        int ind
    )
        : curr_node(node), curr_ind(ind){}


    template<typename T>
    typename BplusTree<T>::Iterator& BplusTree<T>::Iterator::operator++() noexcept {
        if (curr_node != nullptr) {
            if (curr_ind < curr_node->data.size() - 1)
                ++curr_ind;
            else {
                curr_node = curr_node->next();
                curr_ind = 0;
            }
        }
        return *this;
    }

        

    template<typename T>
    const T& BplusTree<T>::Iterator::operator*() const noexcept {
        assert(curr_node && "Iterator for nullptr doesn't have data");
        return curr_node->data[curr_ind];
    }

    template<typename T>
    bool BplusTree<T>::Iterator::operator!=(const Iterator &other) noexcept {
        return curr_node != other.curr_node;
    }

    template<typename T>
    bool BplusTree<T>::Iterator::operator==(const Iterator &other) noexcept {
        return curr_node == other.curr_node;
    }

    template<typename T>
    bool BplusTree<T>::Iterator::empty() const noexcept {
        return curr_node == nullptr;
    }
}