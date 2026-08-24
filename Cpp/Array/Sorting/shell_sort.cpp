#include "Sorting.h"
#include "Visualizer/visualizer.h"

#include <algorithm>

namespace Sorting
{
    void shell_sort(std::vector<int>& arr, Visualizer* viz)
    {
        for (std::size_t gap = arr.size() / 2; gap > 0; gap /= 2)
        {
            for (std::size_t i = gap; i < arr.size(); ++i)
            {
                if (viz && viz->shouldStop()) return;
                const int value = arr[i];
                std::size_t j = i;
                while (j >= gap && arr[j - gap] > value)
                {
                    if (viz) viz->compare(static_cast<int>(j - gap), static_cast<int>(j));
                    arr[j] = arr[j - gap];
                    if (viz) viz->swap(static_cast<int>(j - gap), static_cast<int>(j));
                    j -= gap;
                    if (viz) viz->update(arr);
                }
                arr[j] = value;
                if (viz) viz->update(arr);
            }
        }
        if (viz) viz->finish();
    }
}