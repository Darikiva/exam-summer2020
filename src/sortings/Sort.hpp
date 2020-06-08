#pragma once

#include "Change.hpp"
#include "Type.hpp"

#include <algorithm>
#include <iterator>
#include <variant>
#include <vector>
#include <list>

namespace detail {

/**
 * @brief Applies heapify method to heap
 */
template<typename It, typename Comp>
constexpr void heapify(It first, It last, std::vector<exam::sort::change::Change<It>> &changes, const Comp comparator) {
    if (first == last) {
        return;
    }
    
    size_t begin_pos = 1;
    auto begin = std::next(first);
    while (begin != last) {
        size_t father_pos = (begin_pos - 1) / 2;
        auto father = std::next(first, father_pos);

        auto begin_saved = begin;
        size_t begin_pos_saved = begin_pos;
        while ((begin_pos != 0) && (comparator(*father, *begin))) {
            changes.emplace_back(exam::sort::change::Swap<It>{father, begin});
            std::iter_swap(father, begin);
            begin_pos = father_pos;
            begin = father;
            if (father_pos != 0) {
                father_pos = (father_pos - 1) / 2;
            }
            father = std::next(first, father_pos);
        }
        begin = begin_saved;
        begin_pos = begin_pos_saved;
        std::advance(begin, 1);
        ++begin_pos;
    }
}

/**
 * @brief Restores heap after removing an element
 */
template<typename It, typename Comp>
constexpr void restore_heap(It first, It last, std::vector<exam::sort::change::Change<It>> &changes, Comp comparator) {
    if (first == last) {
        return;
    }

    size_t size = std::distance(first, last);
    size_t current_pos = 0;
    size_t child_pos = 1;
    auto current = first;
    auto child = std::next(first);
    bool move_next = false;

    do {
        move_next = false;
        auto selected_child = child;
        size_t selected_pos = child_pos;
        if (child_pos < size) {
            if (child_pos + 1 < size) {
                if (comparator(*child, *std::next(child))) {
                    selected_child = std::next(child);
                    selected_pos = child_pos + 1;
                } else {
                    selected_child = child;
                    selected_pos = child_pos;
                }
            }
        } else {
            break;
        }
        if (comparator(*current, *selected_child)) {
            move_next = true;
            changes.emplace_back(exam::sort::change::Swap<It>{current, selected_child});
            std::iter_swap(current, selected_child);
            current = selected_child;
            current_pos = selected_pos;
            child_pos = 2 * child_pos + 1;
            if (child_pos < size) {
                child = std::next(first, child_pos);
            }
        }
    } while (move_next);
}

/**
 * @brief Finds first element that does not satisfy predicate
 */
template<typename It, class Comp>
constexpr It iterFind_if(It first, It last, Comp p)
{
    for (; first != last; ++first) {
        if (!p(first)) {
            return first;
        }
    }
    return last;
}

/**
 * @brief Creates a partition of a range
 */
template<typename It, typename Comp>
It iterPartition(It first, It last, Comp p)
{
    first = iterFind_if(first, last, p);
    if (first == last) return first;
 
    for (auto i = std::next(first); i != last; ++i) {
        if (p(i)) {
            std::iter_swap(i, first);
            ++first;
        }
    }
    return first;
}

/**
 * @brief Sorts range with quick sort on forward iterators
 */
template<typename FIter, typename Comp>
constexpr void quickSort(FIter first, FIter last, std::vector<exam::sort::change::Change<FIter>> &changes, Comp comparator, std::forward_iterator_tag) {
    const size_t distance = std::distance(first, last);

    if (distance < 2) {
        return;
    }

    auto end = std::next(first, distance - 1);
    
    changes.emplace_back(exam::sort::change::Swap<FIter>{std::next(first, distance / 2), end});
    std::iter_swap(std::next(first, distance / 2), end);

    auto mid = iterPartition(first, end, [&](const auto &el) {
        if (comparator(*el, *end)) {
            changes.emplace_back(exam::sort::change::Swap<FIter>{el, end});
            return true;
        }
        return false;
    });
    std::iter_swap(mid, end);
    changes.emplace_back(exam::sort::change::SelectPivot<FIter>{mid});

    quickSort(first, mid, changes, comparator, std::forward_iterator_tag());
    quickSort(std::next(mid), last, changes, comparator, std::forward_iterator_tag());
}

/**
 * @brief Sorts range with quick sort on random access iterators
 */
template<typename RAIter, typename Comp>
constexpr void quickSort(RAIter first, RAIter last, std::vector<exam::sort::change::Change<RAIter>> &changes, Comp comparator, std::random_access_iterator_tag) {
    const size_t distance = std::distance(first, last);

    if (distance < 2) {
        return;
    }

    auto end = std::next(first, distance - 1);
    
    changes.emplace_back(exam::sort::change::Swap<RAIter>{std::next(first, distance / 2), end});
    std::iter_swap(std::next(first, distance / 2), end);

    auto mid = iterPartition(first, end, [&](const auto &el) {
        if (comparator(*el, *end)) {
            changes.emplace_back(exam::sort::change::Swap<RAIter>{el, end});
            return true;
        }
        return false;
    });
    std::iter_swap(mid, end);
    changes.emplace_back(exam::sort::change::SelectPivot<RAIter>{mid});

    quickSort(first, mid, changes, comparator, std::random_access_iterator_tag());
    quickSort(std::next(mid), last, changes, comparator, std::random_access_iterator_tag());
}

/**
 * @brief Sorts range with selection sort on random access iterators
 */
template<typename It, typename Comp>
void selectionSort(It first, It last, std::vector<exam::sort::change::Change<It>> &changes, Comp comp, std::bidirectional_iterator_tag) {
        for (auto it = first; it != last; ++it) { 
            auto key = it;
            if (key != first) {
                while ((key != first) && (comp(*key, *std::prev(key)))) {
                    changes.emplace_back(exam::sort::change::Swap<It>{key, std::prev(key)});
                    std::iter_swap(key, std::prev(key));
                    std::advance(key, -1);
                }
            }
        }  
}

/**
 * @brief Sorts range with selection sort on forward iterators
 */
template<typename It, typename Comp>
void selectionSort(It first, It last, std::vector<exam::sort::change::Change<It>> &changes, Comp comp, std::forward_iterator_tag) {
        for (auto it = first; it != last; ++it) { 
            auto key = it;
            if (key != first) {
                auto prev = std::next(first, std::distance(first, key)-1);
                while ((key != first) && (comp(*key, *prev))) {
                    changes.emplace_back(exam::sort::change::Swap<It>{key, prev});
                    std::iter_swap(key, prev);
                    key = std::next(first, std::distance(first, key)-1);
                    if (key != first) {
                        prev = std::next(first, std::distance(first, key)-1);
                    }
                }
            }
        }
}

/**
 * @brief Merges two ranges into first
 */
template<typename It, typename Comp>
void advanced_merge(It first, It middle, It last, std::vector<exam::sort::change::Change<It>> &changes, Comp comp) {
    std::list<typename std::iterator_traits<It>::value_type> buffer(std::distance(first, last));
    std::vector<int> indexes;
    auto buffer_it = buffer.begin();
    auto first_range_it = first;
    auto second_range_it = middle;
    while ((first_range_it != middle) && (second_range_it != last)) {
        if (comp(*first_range_it, *second_range_it)) {
            indexes.push_back(std::distance(first, first_range_it));
            std::iter_swap(buffer_it, first_range_it);
            ++first_range_it;
        } else {
            indexes.push_back(std::distance(first, second_range_it));
            std::iter_swap(buffer_it, second_range_it);
            ++second_range_it;
        }
        ++buffer_it;
    }
    while (first_range_it != middle) {
        indexes.push_back(std::distance(first, first_range_it));
        std::iter_swap(buffer_it, first_range_it);
        ++first_range_it;
        ++buffer_it;
    }
    while (second_range_it != last) {
        indexes.push_back(std::distance(first, second_range_it));
        std::iter_swap(buffer_it, second_range_it);
        ++second_range_it;
        ++buffer_it;
    }
    
    auto t_first = first;
    for (auto it = buffer.begin(); it != buffer.end(); ++it) {
        std::iter_swap(it, t_first);
        ++t_first;
    }
    
    for (int fixed_index = 0; fixed_index < indexes.size(); ++fixed_index) {
        if (indexes[fixed_index] != fixed_index) {
            int pos = fixed_index;
            for (int i = fixed_index; i < indexes.size(); ++i) {
                if (indexes[i] == fixed_index) {
                    pos = i;
                    break;
                }
            }
            std::swap(indexes[pos], indexes[fixed_index]);
            changes.emplace_back(exam::sort::change::Swap{std::next(first, indexes[pos]), std::next(first, indexes[fixed_index])});
        }
    }
}

} // namespace detail

namespace exam::sort {

template<typename T>
struct Sort
{
    static_assert(sizeof(T) == 0, "No specialization found for your type");
};

/**
 * @brief Insertion sort
 */
template<>
struct Sort<type::Insertion>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<exam::sort::change::Change<It>>
    {
        std::vector<exam::sort::change::Change<It>> changes;

        for (; first != last; ++first) {
            for (auto it = std::next(first); it != last; ++it) {
                if (!comp(*first, *it)) {
                    std::iter_swap(first, it);
                    changes.emplace_back(exam::sort::change::Swap{first, it});
                }
            }
        }

        return changes;
    }
    
    template<typename It>
    auto operator()(It first, It last) const -> std::vector<exam::sort::change::Change<It>>
    {
        return (*this)(first, last, std::less{});
    }
};


/**
 * @brief Selection sort
 */
template<>
struct Sort<type::Selection>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<exam::sort::change::Change<It>>
    {
        std::vector<exam::sort::change::Change<It>> changes;

        detail::selectionSort(first, last, changes, comp, typename std::iterator_traits<It>::iterator_category());

        return changes;
    }
    
    template<typename It>
    auto operator()(It first, It last) const -> std::vector<exam::sort::change::Change<It>>
    {
        return (*this)(first, last, std::less{});
    }
};

/**
 * @brief Bubble sort
 */
template<>
struct Sort<type::Bubble>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<exam::sort::change::Change<It>>
    {
        std::vector<exam::sort::change::Change<It>> changes;
        
        if (first == last) {
            return changes;
        }

        bool has_changed = true;
        while (has_changed) {
            has_changed = false;
            auto begin = first;
            auto next_iterator = std::next(begin);
            while (next_iterator != last) {
                if (comp(*next_iterator, *begin)) {
                    changes.emplace_back(exam::sort::change::Swap{next_iterator, begin});
                    std::iter_swap(next_iterator, begin);
                    has_changed = true;
                }
                begin = next_iterator;
                std::advance(next_iterator, 1);
            }
        }
        
        return changes;
    }
    
    template<typename It>
    auto operator()(It first, It last) const -> std::vector<exam::sort::change::Change<It>>
    {
        return (*this)(first, last, std::less{});
    }
};


/**
 * @brief Quick sort 
 */
template<>
struct Sort<type::Quick>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<exam::sort::change::Change<It>>
    {
        std::vector<exam::sort::change::Change<It>> changes;
        
        detail::quickSort(first, last, changes, comp, typename std::iterator_traits<It>::iterator_category());
        
        return changes;
    }
    
    template<typename It>
    auto operator()(It first, It last) const -> std::vector<exam::sort::change::Change<It>>
    {
        return (*this)(first, last, std::less{});
    }
};

/**
 * @brief Merge sort
 */
template<>
struct Sort<type::Merge>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<exam::sort::change::Change<It>>
    {
        std::vector<exam::sort::change::Change<It>> changes;
        

            if (const auto distance = std::distance(first, last); distance > 1) {
                const auto middle = std::next(first, distance / 2);
                changes.emplace_back(exam::sort::change::SelectSubrange<It>{first, middle});
                auto left_changes = Sort<exam::sort::type::Merge>{}(first, middle, comp);
                changes.insert(changes.end(), 
                               std::make_move_iterator(left_changes.begin()), std::make_move_iterator(left_changes.end()));
                changes.emplace_back(exam::sort::change::SelectSubrange<It>{middle, last});
                auto right_changes = Sort<exam::sort::type::Merge>{}(middle, last, comp);
                changes.insert(changes.end(), 
                               std::make_move_iterator(right_changes.begin()), std::make_move_iterator(right_changes.end()));
                
                changes.emplace_back(exam::sort::change::MergeSubranges<It>{first, last});
                detail::advanced_merge(first, middle, last, changes, comp);
            }

            return changes;
        }
        
    template<typename It>
    auto operator()(It first, It last) const -> std::vector<exam::sort::change::Change<It>>
    {
        return (*this)(first, last, std::less{});
    }
};
    

/**
 * @brief Heap sort
 */
template<>
struct Sort<type::Heap>
{
    template<typename It, typename Comp>
    auto operator()(It first, It last, Comp comp) const -> std::vector<exam::sort::change::Change<It>>
    {
        std::vector<exam::sort::change::Change<It>> changes;
        
        detail::heapify(first, last, changes, comp);
        int size = std::distance(first, last);
        --size;
        while (size > 0) {
            auto to_swap = std::next(first, size);
            changes.emplace_back(exam::sort::change::Swap{to_swap, first});
            std::iter_swap(to_swap, first);
            detail::restore_heap(first, std::next(first, size), changes, comp);
            --size;
        }
        
        return changes;
    }
    
    template<typename It>
    auto operator()(It first, It last) const -> std::vector<exam::sort::change::Change<It>>
    {
        return (*this)(first, last, std::less{});
    }
};

} // namespace exam::sort
