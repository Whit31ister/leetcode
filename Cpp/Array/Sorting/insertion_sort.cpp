#include "Sorting.h"

#include "visualizer.h"

namespace Sorting
{
    void insertion_sort(std::vector<int>& arr, Visualizer* viz)
    {
        const auto n = arr.size();

        for (std::size_t i = 1; i < n; ++i)
        {
            const int key = arr[i];
            std::size_t j = i;

            while (j > 0)
            {
                if (viz && viz->shouldStop())
                {
                    return;
                }

                if (viz)
                {
                    viz->compare(static_cast<int>(j - 1), static_cast<int>(j));
                }

                if (arr[j - 1] <= key)
                {
                    break;
                }

                arr[j] = arr[j - 1];

                if (viz)
                {
                    viz->swap(static_cast<int>(j - 1), static_cast<int>(j));
                    viz->update(arr);
                }

                if (viz && viz->shouldStop())
                {
                    return;
                }

                --j;
            }

            arr[j] = key;

            if (viz)
            {
                viz->update(arr);
            }

            if (viz && viz->shouldStop())
            {
                return;
            }
        }

        if (viz)
        {
            viz->finish();
        }
    }
}
