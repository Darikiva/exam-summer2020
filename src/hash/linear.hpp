#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include <type_traits>

namespace exam::hash {
    
template<typename Key, typename Value = Key, typename Hash = std::hash<Key>>
class LinearHash {
public:
    LinearHash(int a, int b, size_t size) : _coef_a(a), _coef_b(b), _size(size), _hashmap(size) {
    }
    
    LinearHash() : _coef_a(1), _coef_b(0), _size(100), _hashmap(100) {
    }
    
    void insert(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        _hashmap[pos].push_back({key, key});
    }
    
    void insert(const Key &key, const Value &value) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        _hashmap[pos].push_back({key, value});
    }
    
    bool exist(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        auto it = _hashmap[pos].begin();
        while ((it != _hashmap[pos].end()) && ((*it).first != key)) {
            ++it;
        }
        if (it == _hashmap[pos].end()) {
            return false;
        }
        return true;
    }
    
    bool erase(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        auto it = _hashmap[pos].begin();
        while ((it != _hashmap[pos].end()) && ((*it).first != key)) {
            ++it;
        }
        if (it == _hashmap[pos].end()) {
            return false;
        }
        _hashmap[pos].erase(it);
        return true;
    }
    

    void set(const Key &key, const Value &value) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        auto it = _hashmap[pos].begin();
        while ((it != _hashmap[pos].end()) && ((*it).first != key)) {
            ++it;
        }
        if (it == _hashmap[pos].end()) {
            return;
        }
        (*it).second = value;
    }
    
    auto get(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        auto it = _hashmap[pos].begin();
        while ((it != _hashmap[pos].end()) && ((*it).first != key)) {
            ++it;
        }
        if (it == _hashmap[pos].end()) {
            return end();
        }
        return it;
    }
    
    auto end() {
        return _hashmap.back().end();
    }
    
protected:
    int _coef_a;
    int _coef_b;
    size_t _size;
    
    std::vector<std::list<std::pair<Key, Value>>> _hashmap;
};

} // namespace exam::hash
