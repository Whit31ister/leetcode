#include "Sorting.h"
#include "Visualizer/visualizer.h"

#include <algorithm>
#include <utility>

namespace Sorting
{
    void comb_sort(std::vector<int>& arr, Visualizer* viz)
    {
        std::size_t gap = arr.size();
        bool swapped = true;
        while (gap > 1 || swapped)
        {
            gap = std::max<std::size_t>(1, gap * 10 / 13);
            swapped = false;
            for (std::size_t i = 0; i + gap < arr.size(); ++i)
            {
                if (viz && viz->shouldStop()) return;
                if (viz) viz->compare(static_cast<int>(i), static_cast<int>(i + gap));
                if (arr[i] > arr[i + gap]) { std::swap(arr[i], arr[i + gap]); swapped = true; if (viz) viz->swap(static_cast<int>(i), static_cast<int>(i + gap)); }
                if (viz) viz->update(arr);
            }
        }
        if (viz) viz->finish();
    }
}