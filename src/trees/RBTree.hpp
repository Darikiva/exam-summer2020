#pragma once
#include <string>
#include <vector>

namespace exam::trees {

    template<typename T>
    class RBTree {
    public:
        RBTree();

        void insert(T& key);

        void erase(const T& key);

        class Iterator;
                
        Iterator search(const T& key);
    private:
        struct Node {
            T key;
            Node* left;
            Node* right;
            Node* parent;
            enum class Color {
                red, black
            };
            Color color;

            Node() :parent(nullptr), left(nullptr),
                right(nullptr), color(Color::black) {}

            Node(T& _key);

            Node* next();

        };
        friend class Node;
        Node* _root;
        static Node* TNILL;

        /**
         * @brief Replaces oldNode with newNode
        */
        void _transplant(Node* oldNode, Node* newNode);

        Node* _min(Node* start);

        void _leftRotate(Node* target);
        void _rightRotate(Node* target);

        void _insertFixup(Node* node);
        void _deleteFixup(Node* node);

        void _delete(Node* z);

        Node* _search(Node* start, const T& key);

    public:
        class Iterator {
        public:
            Iterator();
            Iterator(Node* node);

            const T& operator*() const noexcept;
            bool operator!=(const Iterator &other) noexcept;
            bool operator==(const Iterator &other) noexcept;
            Iterator& operator++() noexcept;

            bool empty() const noexcept;
        private:
            Node* _node;
        };
        friend class Iterator;
    };

    template<typename T>
    typename RBTree<T>::Node* RBTree<T>::TNILL;
}
#include "RBTree.tpp"

