#pragma once

#include "splay_set.hpp"

namespace exam::trees {
    
template<typename Key, typename Value, typename Comparator>
struct PairComparator {
    bool operator()(const std::pair<Key, Value> &left, const std::pair<Key, Value> &right) {
        return Comparator{}(left.first, right.first);
    }
};
    
template<typename Key, typename Value, typename Comparator = std::less<Key>>
class SplayMap : public SplaySet<std::pair<Key, Value>, PairComparator<Key, Value, Comparator>> {
public:
    using typename SplaySet<std::pair<Key, Value>, PairComparator<Key, Value, Comparator>>::Iterator;
    
    Iterator exist(const Key &key) {
        auto curr_node = this->head;
        while (curr_node) {
            if (key == curr_node->value.first) {
                SplaySet<std::pair<Key, Value>, PairComparator<Key, Value, Comparator>>::splay(curr_node);
                return Iterator{this->head};
            }
            if (Comparator{}(key, curr_node->value.first)) {
                curr_node = curr_node->left;
            } else {
                curr_node = curr_node->right;
            }
        }
        return Iterator{nullptr};
    }
    
    Iterator insert(const Key &key, const Value &val) {
        if (exist(key) != Iterator{nullptr}) {
            erase(key);
        }
        return SplaySet<std::pair<Key, Value>, PairComparator<Key, Value, Comparator>>::insert(std::pair<Key, Value>(key, val));
    }
    
    void erase(const Key &key) {
        auto it = exist(key);
        if (!it.get()) {
            return;
        }
        this->head = SplaySet<std::pair<Key, Value>, PairComparator<Key, Value, Comparator>>::merge(it.get()->left, it.get()->right);
        
    }
    
protected:
    using SplaySet<std::pair<Key, Value>, PairComparator<Key, Value, Comparator>>::exist;
};
    
} // namespace exam::trees
