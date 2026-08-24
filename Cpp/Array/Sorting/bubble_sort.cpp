#include "Sorting.h"
#include "visualizer.h"

#include <utility>

namespace Sorting
{
    void bubble_sort(
        std::vector<int>& arr,
        Visualizer* viz)
    {
        const auto n = arr.size();

        for (std::size_t i = 0; i < n; ++i)
        {
            for (std::size_t j = 0; j + 1 < n - i; ++j)
            {
                if (viz && viz->shouldStop())
                {
                    return;
                }

                if (viz)
                {
                    viz->compare(static_cast<int>(j), static_cast<int>(j + 1));
                }

                if (arr[j] > arr[j + 1])
                {
                    std::swap(arr[j], arr[j + 1]);

                    if (viz)
                    {
                        viz->swap(static_cast<int>(j), static_cast<int>(j + 1));
                    }
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
        }

        if (viz)
        {
            viz->finish();
        }
    }
}
