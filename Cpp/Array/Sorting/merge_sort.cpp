#include "Sorting.h"

#include "visualizer.h"

#include <vector>

namespace Sorting
{
    namespace
    {
        bool shouldStop(const Visualizer* viz)
        {
            return viz && viz->shouldStop();
        }

        bool merge(
            std::vector<int>& arr,
            const std::size_t left,
            const std::size_t mid,
            const std::size_t right,
            Visualizer* viz)
        {
            const std::vector<int> leftPart(arr.begin() + static_cast<std::ptrdiff_t>(left),
                                            arr.begin() + static_cast<std::ptrdiff_t>(mid + 1));
            const std::vector<int> rightPart(arr.begin() + static_cast<std::ptrdiff_t>(mid + 1),
                                             arr.begin() + static_cast<std::ptrdiff_t>(right + 1));

            std::size_t i = 0;
            std::size_t j = 0;
            std::size_t k = left;

            while (i < leftPart.size() && j < rightPart.size())
            {
                if (shouldStop(viz))
                {
                    return false;
                }

                if (viz)
                {
                    viz->compare(
                        static_cast<int>(left + i),
                        static_cast<int>(mid + 1 + j));
                }

                if (leftPart[i] <= rightPart[j])
                {
                    arr[k++] = leftPart[i++];
                }
                else
                {
                    arr[k++] = rightPart[j++];
                }

                if (viz)
                {
                    viz->update(arr);
                }
            }

            while (i < leftPart.size())
            {
                if (shouldStop(viz))
                {
                    return false;
                }

                arr[k++] = leftPart[i++];

                if (viz)
                {
                    viz->update(arr);
                }
            }

            while (j < rightPart.size())
            {
                if (shouldStop(viz))
                {
                    return false;
                }

                arr[k++] = rightPart[j++];

                if (viz)
                {
                    viz->update(arr);
                }
            }

            return !shouldStop(viz);
        }

        bool merge_sort_recursive(
            std::vector<int>& arr,
            const std::size_t left,
            const std::size_t right,
            Visualizer* viz)
        {
            if (left >= right)
            {
                return true;
            }

            const std::size_t mid = left + ((right - left) / 2);

            if (!merge_sort_recursive(arr, left, mid, viz))
            {
                return false;
            }

            if (!merge_sort_recursive(arr, mid + 1, right, viz))
            {
                return false;
            }

            return merge(arr, left, mid, right, viz);
        }
    }

    void merge_sort(std::vector<int>& arr, Visualizer* viz)
    {
        if (arr.size() <= 1)
        {
            if (viz)
            {
                viz->finish();
            }

            return;
        }

        if (merge_sort_recursive(arr, 0, arr.size() - 1, viz) && viz)
        {
            viz->finish();
        }
    }
}
