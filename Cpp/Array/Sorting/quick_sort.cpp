#include "Sorting.h"

#include "Visualizer/visualizer.h"

#include <utility>

namespace Sorting
{
    namespace
    {
        bool shouldStop(const Visualizer* viz)
        {
            return viz && viz->shouldStop();
        }

        bool partition(
            std::vector<int>& arr,
            const std::size_t low,
            const std::size_t high,
            std::size_t& pivotIndex,
            Visualizer* viz)
        {
            const int pivot = arr[high];
            std::size_t i = low;

            for (std::size_t j = low; j < high; ++j)
            {
                if (shouldStop(viz))
                {
                    return false;
                }

                if (viz)
                {
                    viz->compare(static_cast<int>(j), static_cast<int>(high));
                    viz->update(arr);
                }

                if (arr[j] < pivot)
                {
                    if (i != j)
                    {
                        std::swap(arr[i], arr[j]);

                        if (viz)
                        {
                            viz->swap(static_cast<int>(i), static_cast<int>(j));
                            viz->update(arr);
                        }
                    }

                    ++i;
                }
            }

            if (i != high)
            {
                std::swap(arr[i], arr[high]);

                if (viz)
                {
                    viz->swap(static_cast<int>(i), static_cast<int>(high));
                    viz->update(arr);
                }
            }

            pivotIndex = i;
            return !shouldStop(viz);
        }

        bool quick_sort_recursive(
            std::vector<int>& arr,
            const std::size_t low,
            const std::size_t high,
            Visualizer* viz)
        {
            if (low >= high)
            {
                return true;
            }

            std::size_t pivotIndex = low;

            if (!partition(arr, low, high, pivotIndex, viz))
            {
                return false;
            }

            if (pivotIndex > 0)
            {
                if (!quick_sort_recursive(arr, low, pivotIndex - 1, viz))
                {
                    return false;
                }
            }

            return quick_sort_recursive(arr, pivotIndex + 1, high, viz);
        }
    }

    void quick_sort(std::vector<int>& arr, Visualizer* viz)
    {
        if (arr.size() <= 1)
        {
            if (viz)
            {
                viz->finish();
            }

            return;
        }

        if (quick_sort_recursive(arr, 0, arr.size() - 1, viz) && viz)
        {
            viz->finish();
        }
    }
}
