#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include <type_traits>
#include <iostream>

namespace exam::hash {
    
template<typename Key, typename Value = Key, typename Hash = std::hash<Key>>
class CuckooHash {
public:
    CuckooHash(int a, int b, size_t size) : _coef_a(a), _coef_b(b), _size(size), _hashmap(size), _hashexist(size, false) {
    }
    
    CuckooHash() : _coef_a(1), _coef_b(1), _size(100), _hashmap(100), _hashexist(100, false) {
    }
    
    void insert(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        int iteration = 0;
        while ((_hashexist[pos]) && (iteration != _size)) {
            pos += _coef_b;
            pos %= _size;
            ++iteration;
        }
        if (iteration == _size) {
            return;
        }
        _hashmap[pos] = std::pair<Key, Value>(key, key);
        _hashexist[pos] = true;
        _curr_size++;
    }
    
    void insert(const Key &key, const Value &value) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        int iteration = 0;
        while ((_hashexist[pos]) && (iteration != _size)) {
            pos += _coef_b;
            pos %= _size;
            ++iteration;
        }
        if (iteration == _size) {
            return;
        }
        _hashmap[pos] = std::pair<Key, Value>(key, value);
        _hashexist[pos] = true;
        _curr_size++;
    }
    
    bool exist(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        auto it = _hashmap[pos];
        int iteration = 0;
        while (((key != _hashmap[pos].first) || (!_hashexist[pos])) && (iteration != _size)) {
            pos += _coef_b;
            pos %= _size;
            ++iteration;
        }
        if (iteration == _size) {
            return false;
        }
        return true;
    }
    
    bool erase(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        auto it = _hashmap[pos];
        int iteration = 0;
        while (((key != _hashmap[pos].first) || (!_hashexist[pos])) && (iteration != _size)) {
            pos += _coef_b;
            pos %= _size;
            ++iteration;
        }
        if (iteration == _size) {
            return false;
        }
        _hashexist[pos] = false;
        _curr_size--;
        return true;
    }
    

    void set(const Key &key, const Value &value) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        int iteration = 0;
        while (((key != _hashmap[pos].first) || (!_hashexist[pos])) && (iteration != _size)) {
            pos += _coef_b;
            pos %= _size;
            ++iteration;
        }
        if (iteration == _size) {
            return;
        }
        
        _hashmap[pos].second = value;
    }
    
    auto get(const Key &key) {
        size_t pos = (_coef_a * Hash{}(key) + _coef_b) % _size;
        int iteration = 0;
        while (((key != _hashmap[pos].first) || (!_hashexist[pos])) && (iteration != _size)) {
            pos += _coef_b;
            pos %= _size;
            ++iteration;
        }
        if (iteration == _size) {
            return end();
        }
        return (_hashmap.begin() + pos);
    }
    
    auto end() {
        return _hashmap.end();
    }
    
protected:
    int _coef_a;
    int _coef_b;
    size_t _size;
    size_t _curr_size = 0;
    
    std::vector<std::pair<Key, Value>> _hashmap;
    std::vector<bool> _hashexist;
};

} // namespace exam::hash

