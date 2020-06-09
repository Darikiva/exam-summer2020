#pragma once
#include <vector>
#include <memory>
#include <algorithm>
using std::vector;
using std::shared_ptr;

namespace exam::trees {

    template <typename T>
    class BTree {
    public:
        explicit BTree(int min_degree);
        ~BTree() = default;

        class Iterator;

        /**
        * @brief Insert element in the tree with Template parameter key
        */
        void insert(const T& key);

        /**
         * @brief remove element from the tree with Template parameter key
         * @description if there is no element with this key - nothing does
        */
        void remove(const T& key) noexcept;

        /**
         * @brief simple print tree in console
         * @description can be done with Iterators
        */
        void print() const noexcept;

        /**
         * @brief: function to find element by value
         * @return return BIterator of current element (or BIterator of nullptr)
         */
        Iterator find(const T& key) const noexcept;

        /**
         * @return: BIterator of the smallest element in tree tree
         */
        Iterator begin() const noexcept;

        /**
         * @return: BIterator of the greatest element in tree tree
         */
        Iterator end() const noexcept;

//        template<typename OStream>
//        friend OStream& operator<<(OStream& os, const BTree& t) {
//            if (t.root)
//                t.root->print(os);
//            return os;
//        }

    public:
        /**
        * @brief: Minimum degree of all nodes in BTree
        */
        int min_degree;

    public:
        class BNode : public std::enable_shared_from_this<BNode> {
        public:
            explicit BNode(bool is_leaf, int min_degree);
            ~BNode() {
                keys.clear();
                children.clear();
            }

            std::shared_ptr<BNode> next() noexcept {
                if (this->is_leaf) {
                    if (this->index == this->keys.size() - 1 && this->parent) {
                        auto current = this->shared_from_this();
                        // move up until there is prev value or root
                        while (current->parent && current->parent->keys.size() == current->getParentIndex()) {
                            current = current->parent;
                        }
                        if (current->parent) {
                            current->parent->index = current->getParentIndex();
                            return current->parent;
                        }
                        return nullptr;
                    }
                    auto current = this->shared_from_this();
                    current->index += 1;
                    return current;
                }
                auto current = this->children[this->index + 1];
                while (!current->is_leaf)
                    current = current->children[0];

                current->index = 0;
                return current;
            }
            std::shared_ptr<BNode> previous() noexcept {
                if (this->is_leaf) {
                    if (this->index == 0 && this->parent) {
                        auto current = this->shared_from_this();
                        // move up until there is prev value or root
                        while (current->parent && current->getParentIndex() == 0) {
                            current = current->parent;
                        }
                        if (current->parent) {
                            current->parent->index = current->getParentIndex();
                            return current->parent;
                        }
                        return nullptr;
                    }
                    auto current = this->shared_from_this();
                    current->index -= 1;
                    return current;
                }
                auto current = this->children[this->index];
                while (!current->is_leaf)
                    current = current->children[current->keys.size()];

                // Return the last key of the leaf
                current->index = current->keys.size() - 1;
                return current;
            }

            /**
            * @brief: Print all elements rooted with element
            */
            void print();

            /**
            * @brief: Insert element but with rule that this element is not full
            */
            void insertNonFull(const T& key);


            /**
            * @return: BIterator based on find function for Node
            */
            Iterator findIterator(const T& key);

            /**
            * @return: index of this element in parent->children array
            */
            int getParentIndex();

            /**
            * @brief: Finds a key in subtree rooted with this node.
            * @description returns nullptr if key is not present
            */
            std::shared_ptr<BNode> find(T key);


            /**
            * @brief: returns the index of the first key that is greater or equal to key
            */
            int findKey(T key);

            /**
            * @brief: A wrapper function to remove the key key in subtree rooted with this node
            */
            void remove(T key);

            /**
            * @description: remove the key present in idx-th position in this node which is a leaf
            */
            void removeFromLeaf(int idx);

            /**
            * @description: remove the key present in idx-th position in this node which is a non-leaf
            */
            void removeFromNonLeaf(int idx);


            /**
            * @description: get the predecessor of the key- where the key
            * is present in the idx-th position in the node
            */
            T getPred(int idx);

            /**
            * @description: get the successor of the key- where the key
            * is present in the idx-th position in the node
            */
            T getSucc(int idx);


            /**
            * @description: fill up the child node present in the idx-th
            * position in the children[] array if that child has less than t-1 keys
            */
            void fill(int idx);

            /**
            * @description: borrow a key from the children[idx-1]-th node and place
            * it in children[idx]th node
            */
            void borrowFromPrev(int idx);

            /**
            * @description: borrow a key from the children[idx+1]-th node and place
            * it in children[idx]th node
            */
            void borrowFromNext(int idx);

            /**
            * @description: merge idx-th child of the node with (idx+1)th child of the node
            */
            void merge(int idx);

            /**
            * @description: A utility function to split the child `child` of this node. `index` is index of child in
            * child array children[].  The Child y must be full when this function is called
            */
            void splitChild(int index, std::shared_ptr<BNode> child);

        public:
            std::vector<T> keys; /**< stores keys in every BNode */
            std::vector<std::shared_ptr<BNode>> children; /**< stores children in every BNode */
            bool is_leaf; /**< true if this BNode is leaf */
            int min_degree; /**< Min degree of current BNode */
            int index; /**< index of current key in keys (-1 if it doesn't need) */
            std::shared_ptr<BNode> parent; /**< pointer to parent */
        };

    public:
        std::shared_ptr<BNode> root;

    public:
        class Iterator {
        public:
            friend class BTree;

            Iterator(std::shared_ptr<BNode> node);

            const T& operator*() const noexcept;
            bool operator!=(const Iterator &other) noexcept;
            bool operator==(const Iterator &other) noexcept;
            Iterator& operator++() noexcept;

        protected:
            std::shared_ptr<typename BTree<T>::BNode> curr_node;
        };
    };


} // namespace exam::trees

#include "BTree.tpp"