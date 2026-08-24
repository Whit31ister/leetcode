#pragma once

#include <vector>

namespace Sorting
{
    class Visualizer;

    void bubble_sort(
        std::vector<int>& arr,
        Visualizer* viz = nullptr);

    void selection_sort(
        std::vector<int>& arr,
        Visualizer* viz = nullptr);

    void insertion_sort(
        std::vector<int>& arr,
        Visualizer* viz = nullptr);

    void merge_sort(
        std::vector<int>& arr,
        Visualizer* viz = nullptr);

    void quick_sort(
        std::vector<int>& arr,
        Visualizer* viz = nullptr);

    void shell_sort(std::vector<int>& arr, Visualizer* viz = nullptr);
    void heap_sort(std::vector<int>& arr, Visualizer* viz = nullptr);
    void counting_sort(std::vector<int>& arr, Visualizer* viz = nullptr);
    void cocktail_sort(std::vector<int>& arr, Visualizer* viz = nullptr);
    void comb_sort(std::vector<int>& arr, Visualizer* viz = nullptr);

}
