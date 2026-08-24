#include "Sorting.h"

#include "visualizer.h"

#include <utility>

namespace Sorting
{
    void selection_sort(std::vector<int>& arr, Visualizer* viz)
    {
        const auto n = arr.size();

        for (std::size_t i = 0; i < n; ++i)
        {
            std::size_t minIndex = i;

            for (std::size_t j = i + 1; j < n; ++j)
            {
                if (viz && viz->shouldStop())
                {
                    return;
                }

                if (viz)
                {
                    viz->compare(static_cast<int>(j), static_cast<int>(minIndex));
                }

                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }

                if (viz)
                {
                    viz->update(arr);
                }

                if (viz && viz->shouldStop())
                {
                    return;
                }
            }

            if (minIndex != i)
            {
                std::swap(arr[i], arr[minIndex]);

                if (viz)
                {
                    viz->swap(static_cast<int>(i), static_cast<int>(minIndex));
                    viz->update(arr);
                }

                if (viz && viz->shouldStop())
                {
                    return;
                }
            }
        }

        if (viz)
        {
            viz->finish();
        }
    }
}
