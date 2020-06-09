#pragma once
#include <vector>
#include <memory>
#include <algorithm>
using std::vector;
using std::shared_ptr;

namespace exam::trees {

    template <typename T>
    class BplusTree {
    public:
        BplusTree(const int m);
        ~BplusTree();

        class Iterator;

        void insert(const int ind, const T& key);
        void remove(const int ind);
        Iterator search(const T& val);

        template<typename OStream>
        friend OStream& operator<<(OStream& os, const BplusTree& t) {
            if (t.root)
                t.root->print(os);
            return os;
        }

    private:
        const int M, MININD;

    public:
        struct BplusNode;
        typedef shared_ptr<BplusNode> NodePtr;
        struct BplusNode {
            vector<int> indexes;
            NodePtr parent;

            vector<NodePtr> children;

            vector<T> data;
            NodePtr nxt;
            NodePtr prv;

            BplusNode() :indexes(vector<int>()), parent(nullptr), nxt(nullptr), prv(nullptr), children(vector<NodePtr>()), data(vector<T>()) {}
            ~BplusNode() {
                indexes.clear();
                children.clear();
                data.clear();
            }

            bool is_leaf() const {
                return children.size() == 0;
            }

            NodePtr next() const noexcept {
                return indexes[0] < nxt->indexes[0] ? nxt : nullptr;
            }
            NodePtr prev() const noexcept {
                return  indexes[0] > prv->indexes[0] ? prv : nullptr;
            }

            NodePtr left() const noexcept;
            NodePtr right() const noexcept;

            template<typename OStream>
            void print(OStream& os, int level = 1) {
                for (int i = 0; i < indexes.size(); ++i) {
                    if (!this->is_leaf())
                        os << indexes[i] << ", ";
                    else
                        os << indexes[i] << '{' << data[i] << '}' << ", ";
                }
                os << '\n';
                for (int i = 0; i < children.size(); ++i) {
                    for (int j = 0; j < level; ++j)
                        os << '\t';
                    children[i]->print(os, level + 1);
                }
            }
        };
    private:
        NodePtr root;
        NodePtr minNode;

    private:
        ///Utility functions for insert and remove
        int _min(NodePtr start) const;
        void split(NodePtr ptr);
        void borrowLeft(NodePtr ptr);
        void borrowRight(NodePtr ptr);
        NodePtr merge(NodePtr ptr) const noexcept;
        void shrink();
    
    public:
        class Iterator {
        public:
            friend class BplusTree;

            Iterator(std::shared_ptr<BplusNode> node, int ind = 0);

            const T& operator*() const noexcept;
            bool operator!=(const Iterator &other) noexcept;
            bool operator==(const Iterator &other) noexcept;
            Iterator& operator++() noexcept;

            bool empty() const noexcept;

        protected:
            std::shared_ptr<typename BplusTree<T>::BplusNode> curr_node;
            int curr_ind;
        };
    };


} // namespace exam::trees

#include "BplusTree.tpp"