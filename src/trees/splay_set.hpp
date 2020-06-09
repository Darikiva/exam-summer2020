#pragma once

#include <memory>

namespace exam::trees {
    
template<typename T>
class TreeNode {
public:
    TreeNode(const T value_) : value(value_) {
    }
    T value;
    
    std::shared_ptr<TreeNode> father;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
};
    
template<typename T, typename Comparator = std::less<T>>
class SplaySet
{
public:
    class Iterator {
    private:
        std::shared_ptr<TreeNode<T>> node;
    public:
        std::shared_ptr<TreeNode<T>> get() {
            return node;
        }
        
        friend SplaySet;
        Iterator(std::shared_ptr<TreeNode<T>> node) : node(node) {}

        Iterator &operator++() {
            auto new_node = node;
            if (new_node->right) {
                new_node = new_node->right;
                while (new_node->left) {
                    new_node = new_node->left;
                }
                node = new_node;
                return *this;
            }
            new_node = new_node->father;
            while (new_node) {
                if (Comparator{}(node->value, new_node->value)) {
                    node = new_node;
                    return *this;
                }
                new_node = new_node->father;
            }
            node = new_node;
            return *this;
        }

        bool operator==(const Iterator &other) {
            return node == other.node;
        }
        
        bool operator!=(const Iterator &other) {
            return node != other.node;
        }

        T operator*() {
            return node->value;
        }
    };
    
    SplaySet() {
    }
    
    Iterator exist(const T &key) {
        auto curr_node = head;
        while (curr_node) {
            if (key == curr_node->value) {
                splay(curr_node);
                return Iterator{head};
            }
            if (comp(key, curr_node->value)) {
                curr_node = curr_node->left;
            } else {
                curr_node = curr_node->right;
            }
        }
        return Iterator{nullptr};
    }
    
    Iterator insert(const T &key) {
        if (auto it = exist(key); it != Iterator{nullptr}) {
            return it;
        }
        
        auto curr_node = head;
        if (!curr_node) {
            head = std::make_shared<TreeNode<T>>(key);
        } else {
        while (curr_node) {
            if (comp(key, curr_node->value)) {
                if (!curr_node->left) {
                    curr_node->left = std::make_shared<TreeNode<T>>(key);
                    curr_node->left->father = curr_node;
                    curr_node = curr_node->left;
                    break;
                }
                curr_node = curr_node->left;
            } else {
                if (!curr_node->right) {
                    curr_node->right = std::make_shared<TreeNode<T>>(key);
                    curr_node->right->father = curr_node;
                    curr_node = curr_node->right;
                    break;
                }
                curr_node = curr_node->right;
            }
        }
        splay(curr_node);
        }
        return Iterator{head};
    }
    
    void erase(const T &key) {
        auto it = exist(key);
        if (!it.node) {
            return;
        }
        this->head = merge(it.node->left, it.node->right);
    }
    
    Iterator end() {
        return Iterator{nullptr};
    }
    
    Iterator begin() {
        auto curr_node = head;
        while (head && head->left) {
            head = head->left;
        }
        return Iterator{head};
    }
    
//     template<typename Comp, typename Type>
//     friend SplaySet<Type, Comp> unite(SplaySet<Type, Comp> &t1, SplaySet<Type, Comp> &t2);
    
protected:
    std::shared_ptr<TreeNode<T>> head;
    Comparator comp;
    
    std::shared_ptr<TreeNode<T>> zig(std::shared_ptr<TreeNode<T>> node) {
        auto father = node->father;
        
        if (father->left == node) { // Left
            auto temp = node->right;
            father->father = node;
            node->father = nullptr;
            node->right = father;
            father->left = temp;
            if (temp) {
                temp->father = father;
            }
        } else { // Right
            auto temp = node->left;
            father->father = node;
            node->father = nullptr;
            node->left = father;
            father->right = temp;
            if (temp) {
                temp->father = father;
            }
        }
        this->head = node;
        return node;
    }
    
    std::shared_ptr<TreeNode<T>> zig_zig(std::shared_ptr<TreeNode<T>> node) {
        auto father = node->father;
        auto grand = father->father;
        
        if (father->left == node) { // Left
            auto b = node->right;
            auto c = father->right;
            node->father = grand->father;
            father->father = node;
            grand->father = father;
            
            node->right = father;
            father->right = grand;
            father->left = b;
            if (b) {
                b->father = father;
            }
            grand->left = c;
            if (c) {
                c->father = grand;
            }
        } else { // Right
            auto b = node->left;
            auto c = father->left;
            node->father = grand->father;
            father->father = node;
            grand->father = father;
            
            node->left = father;
            father->left = grand;
            father->right = b;
            if (b) {
                b->father = father;
            }
            grand->right = c;
            if (c) {
                c->father = grand;
            }
        }
        if (node->father) {
            if (node->father->left == grand) {
                node->father->left = node;
            } else {
                node->father->right = node;
            }
        } else {
            this->head = node;
        }
        return node;
    }
    
    std::shared_ptr<TreeNode<T>> zig_zag(std::shared_ptr<TreeNode<T>> node) {
        auto father = node->father;
        auto grand = father->father;
        
        if (father->left == node) { // Left
            auto b = node->right;
            auto c = node->left;
            node->father = grand->father;
            father->father = node;
            grand->father = node;
            
            node->left = grand;
            node->right = father;
            father->left = b;
            grand->right = c;
            if (b) {
                b->father = father;
            }
            if (c) {
                c->father = grand;
            }
        } else { // Right
            auto b = node->left;
            auto c = node->right;
            node->father = grand->father;
            father->father = node;
            grand->father = node;
            
            node->left = father;
            node->right = grand;
            father->right = b;
            grand->left = c;
            if (b) {
                b->father = father;
            }
            if (c) {
                c->father = grand;
            }
        }
        if (node->father) {
            if (node->father->left == grand) {
                node->father->left = node;
            } else {
                node->father->right = node;
            }
        } else {
            this->head = node;
        }
        return node;
    }

    void splay(std::shared_ptr<TreeNode<T>> node) {
        auto father = node->father;
        if (father) {
            auto grand = father->father;
            if (grand) {
                if (((grand->left == father) && (father->left == node)) || 
                    ((grand->right == father) && (father->right == node))) {
                    return splay(zig_zig(node));
                } else {
                    return splay(zig_zag(node));
                }
            } else {
                zig(node);
            }
        } else {
            return;
        }
    }
    
    std::shared_ptr<TreeNode<T>> merge(std::shared_ptr<TreeNode<T>> t1, std::shared_ptr<TreeNode<T>> t2) {
        if (!t1 && !t2) return nullptr;
        if (!t1) {
            t2->father = nullptr;
            return t2;
        }
        if (!t2) {
            t1->father = nullptr;
            return t1;
        }
        
        auto max = t1;
        while (max->right) {
            max = max->right;
        }
        splay(max);
        max->right = t2;
        t2->father = max;
        return max;
    }
};

template<typename Comp, typename Type>
SplaySet<Type, Comp> unite(SplaySet<Type, Comp> &t1, SplaySet<Type, Comp> &t2) {
        SplaySet<Type, Comp> result;
        for (auto elem : t1) {
            result.insert(elem);
        }
        for (auto elem : t2) {
            result.insert(elem);
        }
        return result;
}

template<typename Comp, typename Type>
SplaySet<Type, Comp> cross(SplaySet<Type, Comp> &t1, SplaySet<Type, Comp> &t2) {
        SplaySet<Type, Comp> result;
        for (auto elem : t1) {
            if (t2.exist(elem) != t2.end()) {
                result.insert(elem);
            }
        }
        return result;
}

template<typename Comp, typename Type>
SplaySet<Type, Comp> symmertical_cross(SplaySet<Type, Comp> &t1, SplaySet<Type, Comp> &t2) {
        SplaySet<Type, Comp> result;
        for (auto elem : t1) {
            if (t2.exist(elem) == t2.end()) {
                result.insert(elem);
            }
        }
        return result;
}

} // namespace exam::trees
