#pragma

#include "BTree.hpp"
#include <iostream>
#include <cassert>

namespace exam::trees {
    template<typename T>
    void BTree<T>::insert(const T &key) {
        if (root == nullptr) {
            root = std::make_shared<BNode>(true, min_degree);
            root->keys.push_back(key);
        } else // If tree is not empty
        {
            // If root is full, then tree grows in height
            if (root->keys.size() == 2 * min_degree - 1) {
                // Allocate memory for new root
                auto new_root = std::make_shared<BNode>(false, min_degree);

                // Make old root as child of new root
                new_root->children.push_back(root);

                root->parent = new_root;
                // Split the old root and move 1 key to the new root
                new_root->splitChild(0, root);

                // New root has two children now.  Decide which of the
                // two children is going to have new key
                int i = 0;
                if (new_root->keys[0] < key)
                    i++;
                new_root->children[i]->insertNonFull(key);

                // Change root
                root = new_root;
            } else  // If root is not full, call insertNonFull for root
                root->insertNonFull(key);
        }
    }


    template<typename T>
    void BTree<T>::remove(const T &key) noexcept {
        if (root == nullptr) {
//        std::cout << "The tree is empty\n";
            return;
        }

        // Call the remove function for root
        root->remove(key);

        // If the root node has 0 keys, make its first child as the new root
        //  if it has a child, otherwise set root as NULL
        if (root->keys.size() == 0) {
            if (root->is_leaf)
                root = nullptr;
            else
                root = root->children[0];
        }
    }

    template<typename T>
    typename BTree<T>::Iterator BTree<T>::find(const T &key) const noexcept {
        if (root) {
            return root->findIterator(key);
        }
        return Iterator(nullptr);
    }

    template<typename T>
    void BTree<T>::BNode::print() {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!is_leaf)
                children[i]->print();
            std::cout << keys[i] << " ";
        }

        if (!is_leaf)
            children[i]->print();
    }


    template<typename T>
    void BTree<T>::print() const noexcept {
        if (root) {
            root->print();
        }
    }

    template<typename T>
    typename BTree<T>::Iterator BTree<T>::begin() const noexcept {
        auto temp = root;
        temp->index = 0;

        while (!temp->is_leaf) {
            temp = temp->children[0];
            temp->index = 0;
        }

        return Iterator(temp);
    }

    template<typename T>
    typename BTree<T>::Iterator BTree<T>::end() const noexcept {
        return Iterator(nullptr);
    }

    template<typename T>
    BTree<T>::BTree(int _min_degree) {
        root = nullptr;
        min_degree = _min_degree;
    }

    template<typename T>
    int BTree<T>::BNode::getParentIndex() {
        auto child = this->shared_from_this();
        if (!child->parent) return -1;

        int counter = 0;
        for (auto elem:child->parent->children) {
            if (elem == child)
                return counter;
            counter++;
        }
        return -1;
    }

    template<typename T>
    std::shared_ptr<typename BTree<T>::BNode> BTree<T>::BNode::find(T key) {
        int i = 0;
        auto current = this->shared_from_this();
        while (i < current->keys.size() && key > current->keys[i])
            i++;

        if (current->keys[i] == key) {
            current->index = i;
            return current;
        }


        if (current->is_leaf)
            return nullptr;

        return current->children[i]->find(key);
    }

    template<typename T>
    typename BTree<T>::Iterator BTree<T>::BNode::findIterator(const T &key) {
        return Iterator(this->find(key));
    }


    template<typename T>
    BTree<T>::BNode::BNode(bool _is_leaf, int _min_degree) {
        index = -1;
        is_leaf = _is_leaf;
        parent = nullptr;
        min_degree = _min_degree;
        keys.reserve(2 * min_degree - 1);
        children.reserve(2 * min_degree);
    }

    template<typename T>
    void BTree<T>::BNode::insertNonFull(const T &key) {
        // Initialize index as index of rightmost element
        int i = keys.size() - 1;


        if (is_leaf) {
            while (i >= 0 && keys[i] > key) {
                i--;
            }

            keys.insert(keys.begin() + i + 1, key);
        } else // If this node is not leaf
        {
            // Find the child which is going to have the new key
            while (i >= 0 && keys[i] > key)
                i--;

            if (children[i + 1]->keys.size() == 2 * min_degree - 1) {

                children[i + 1]->parent = this->shared_from_this();

                splitChild(i + 1, children[i + 1]);

                if (keys[i + 1] < key)
                    i++;
            }
            children[i + 1]->insertNonFull(key);
        }
    }

    template<typename T>
    void BTree<T>::BNode::splitChild(int ind, std::shared_ptr <BNode> child) {
        auto new_node = std::make_shared<BNode>(child->is_leaf, child->min_degree);

        for (int j = 0; j < min_degree - 1; j++)
            new_node->keys.push_back(child->keys[j + min_degree]);


        if (!child->is_leaf) {
            for (int j = 0; j < min_degree; j++) {
                new_node->children.push_back(child->children[j + min_degree]);
                new_node->children[new_node->children.size() - 1]->parent = new_node;
            }

        }

        child->keys.resize(min_degree - 1);
        child->children.resize(min_degree);
        children.insert(children.begin() + ind + 1, new_node);
        new_node->parent = child->parent;

        keys.insert(keys.begin() + ind, child->keys[min_degree - 1]);
    }

    template<typename T>
    int BTree<T>::BNode::findKey(T key) {
        int idx = 0;
        while (idx < keys.size() && keys[idx] < key)
            ++idx;
        return idx;
    }

    template<typename T>
    void BTree<T>::BNode::remove(T key) {
        int idx = this->findKey(key);

        // The key to be removed is present in this node
        if (idx < keys.size() && keys[idx] == key) {

            // If the node is a leaf node - removeFromLeaf is called
            // Otherwise, removeFromNonLeaf function is called
            if (is_leaf)
                removeFromLeaf(idx);
            else
                removeFromNonLeaf(idx);
        } else {
            // If this node is a leaf node, then the key is not present in tree
            // Error
            if (is_leaf)
                return;
//        assert(!is_leaf);

            // The key to be removed is present in the sub-tree rooted with this node
            // The flag indicates whether the key is present in the sub-tree rooted
            // with the last child of this node
            bool flag = idx == keys.size();

            // If the child where the key is supposed to exist has less that t keys,
            // we fill that child
            if (children[idx]->keys.size() < min_degree)
                fill(idx);

            // If the last child has been merged, it must have merged with the previous
            // child and so we recurse on the (idx-1)th child. Else, we recurse on the
            // (idx)th child which now has atleast t keys
            if (flag && idx > keys.size())
                children[idx - 1]->remove(key);
            else
                children[idx]->remove(key);
        }
    }

    template<typename T>
    void BTree<T>::BNode::removeFromLeaf(int idx) {
        keys.erase(keys.begin() + idx);
    }

    template<typename T>
    void BTree<T>::BNode::removeFromNonLeaf(int idx) {

        T key = keys[idx];

        if (children[idx]->keys.size() >= min_degree) {
            T pred = getPred(idx);
            keys[idx] = pred;
            children[idx]->remove(pred);
        } else if (children[idx + 1]->keys.size() >= min_degree) {
            T succ = getSucc(idx);
            keys[idx] = succ;
            children[idx + 1]->remove(succ);
        } else {
            merge(idx);
            children[idx]->remove(key);
        }
    }

    template<typename T>
    T BTree<T>::BNode::getPred(int idx) {
        this->index = idx;
        auto prev = std::dynamic_pointer_cast<BNode>(this->previous());
        return prev->keys[prev->index];
    }

    template<typename T>
    T BTree<T>::BNode::getSucc(int idx) {
        this->index = idx;
        auto next = std::dynamic_pointer_cast<BNode>(this->next());
        return next->keys[next->index];
    }

    template<typename T>
    void BTree<T>::BNode::fill(int idx) {
        if (idx != 0 && children[idx - 1]->keys.size() >= min_degree)
            borrowFromPrev(idx);

        else if (idx != keys.size() && children[idx + 1]->keys.size() >= min_degree)
            borrowFromNext(idx);

        else {
            if (idx != keys.size())
                merge(idx);
            else
                merge(idx - 1);
        }
    }

    template<typename T>
    void BTree<T>::BNode::borrowFromPrev(int idx) {
        std::shared_ptr <BNode> child = children[idx];
        std::shared_ptr <BNode> sibling = children[idx - 1];

        // The last key from C[idx-1] goes up to the parent and key[idx-1]
        // from parent is inserted as the first key in C[idx]. Thus, the  loses
        // sibling one key and child gains one key

        child->keys.insert(child->keys.begin(), keys[idx - 1]);

        // If C[idx] is not a leaf, move all its child pointers one step ahead
        if (!child->is_leaf) {
            child->children.insert(child->children.begin(), sibling->children[sibling->keys.size()]);
            child->children[0]->parent = child;
            sibling->children.pop_back();
        }

        // Moving the key from the sibling to the parent
        // This reduces the number of keys in the sibling
        keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
        sibling->keys.pop_back();
    }

    template<typename T>
    void BTree<T>::BNode::borrowFromNext(int idx) {
        std::shared_ptr <BNode> child = children[idx];
        std::shared_ptr <BNode> sibling = children[idx + 1];

        // keys[idx] is inserted as the last key in C[idx]
        child->keys.push_back(keys[idx]);

        if (!(child->is_leaf)) {
            child->children.push_back(sibling->children[0]);
            child->children[child->children.size() - 1]->parent = child;
        }

        //The first key from sibling is inserted into keys[idx]
        keys[idx] = sibling->keys[0];

        sibling->keys.erase(sibling->keys.begin());

        if (!sibling->is_leaf) {
            sibling->children.erase(sibling->children.begin());
        }
    }

    template<typename T>
    void BTree<T>::BNode::merge(int idx) {
        std::shared_ptr <BNode> child = children[idx];
        std::shared_ptr <BNode> sibling = children[idx + 1];

        // Pulling a key from the current node and inserting it into (t-1)th
        // position of C[idx]
        child->keys.push_back(keys[idx]);

        // Copying the keys from C[idx+1] to C[idx] at the end
        for (int i = 0; i < sibling->keys.size(); ++i)
            child->keys.push_back(sibling->keys[i]);

        // Copying the child pointers from C[idx+1] to C[idx]
        if (!child->is_leaf) {
            for (int i = 0; i <= sibling->keys.size(); ++i) {
                child->children.push_back(sibling->children[i]);
                child->children[child->children.size() - 1]->parent = child;
            }
        }

        // to erase the gap created by moving keys[idx] to C[idx]
        keys.erase(keys.begin() + idx);

        // Moving the child pointers after (idx+1) in the current node one
        // step before
        children.erase(children.begin() + idx + 1);
    }

    template<typename T>
    BTree<T>::Iterator::Iterator(
            std::shared_ptr<typename BTree<T>::BNode> node
    )
            : curr_node(node){}


    template<typename T>
    typename BTree<T>::Iterator& BTree<T>::Iterator::operator++() noexcept {
        if (curr_node != nullptr){
            curr_node = curr_node->next();
        }
        return *this;
    }



    template<typename T>
    const T& BTree<T>::Iterator::operator*() const noexcept {
        assert(curr_node && "Iterator for nullptr doesn't have data");
        return curr_node->keys[curr_node->index];
    }

    template<typename T>
    bool BTree<T>::Iterator::operator!=(const Iterator &other) noexcept {
        return curr_node != other.curr_node;
    }

    template<typename T>
    bool BTree<T>::Iterator::operator==(const Iterator &other) noexcept {
        return curr_node == other.curr_node;
    }
} // namespace exam::trees