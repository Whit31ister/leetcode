#ifndef SORTING_ALGORITHMS_HPP
#define SORTING_ALGORITHMS_HPP

#include <functional>
#include <iterator>
#include <utility>
#include <vector>

namespace sorting {

template <typename RandomIt, typename Compare = std::less<>>
void bubble_sort(RandomIt first, RandomIt last, Compare compare = {}) {
    if (first == last) {
        return;
    }

    for (auto end = last; end != first; --end) {
        bool swapped = false;
        for (auto current = first; std::next(current) != end; ++current) {
            auto next = std::next(current);
            if (compare(*next, *current)) {
                std::iter_swap(current, next);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

template <typename RandomIt, typename Compare = std::less<>>
void selection_sort(RandomIt first, RandomIt last, Compare compare = {}) {
    for (auto current = first; current != last; ++current) {
        auto smallest = current;
        for (auto candidate = std::next(current); candidate != last; ++candidate) {
            if (compare(*candidate, *smallest)) {
                smallest = candidate;
            }
        }
        std::iter_swap(current, smallest);
    }
}

template <typename RandomIt, typename Compare = std::less<>>
void insertion_sort(RandomIt first, RandomIt last, Compare compare = {}) {
    if (first == last) {
        return;
    }

    for (auto current = std::next(first); current != last; ++current) {
        auto value = std::move(*current);
        auto position = current;
        while (position != first && compare(value, *std::prev(position))) {
            *position = std::move(*std::prev(position));
            --position;
        }
        *position = std::move(value);
    }
}

namespace detail {
template <typename RandomIt, typename Compare>
void merge_sort(RandomIt first, RandomIt last, Compare compare) {
    auto length = std::distance(first, last);
    if (length < 2) {
        return;
    }

    auto middle = first;
    std::advance(middle, length / 2);
    merge_sort(first, middle, compare);
    merge_sort(middle, last, compare);

    using value_type = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<value_type> merged;
    merged.reserve(static_cast<std::size_t>(length));

    auto left = first;
    auto right = middle;
    while (left != middle && right != last) {
        if (compare(*right, *left)) {
            merged.push_back(std::move(*right++));
        } else {
            merged.push_back(std::move(*left++));
        }
    }
    merged.insert(merged.end(), std::make_move_iterator(left), std::make_move_iterator(middle));
    merged.insert(merged.end(), std::make_move_iterator(right), std::make_move_iterator(last));
    std::move(merged.begin(), merged.end(), first);
}
}  // namespace detail

template <typename RandomIt, typename Compare = std::less<>>
void merge_sort(RandomIt first, RandomIt last, Compare compare = {}) {
    detail::merge_sort(first, last, compare);
}

template <typename RandomIt, typename Compare = std::less<>>
void quick_sort(RandomIt first, RandomIt last, Compare compare = {}) {
    if (first == last || std::next(first) == last) {
        return;
    }

    auto pivot = std::prev(last);
    auto boundary = first;
    for (auto current = first; current != pivot; ++current) {
        if (compare(*current, *pivot)) {
            std::iter_swap(current, boundary++);
        }
    }
    std::iter_swap(boundary, pivot);
    quick_sort(first, boundary, compare);
    quick_sort(std::next(boundary), last, compare);
}

}  // namespace sorting

#endif
