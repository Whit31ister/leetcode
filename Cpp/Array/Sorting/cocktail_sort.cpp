#include "Sorting.h"
#include "Visualizer/visualizer.h"

#include <utility>

namespace Sorting
{
    void cocktail_sort(std::vector<int>& arr, Visualizer* viz)
    {
        if (arr.empty()) { if (viz) viz->finish(); return; }
        std::size_t left = 0;
        std::size_t right = arr.size() - 1;
        bool changed = true;
        while (changed && left < right)
        {
            changed = false;
            for (std::size_t i = left; i < right; ++i)
            {
                if (viz && viz->shouldStop()) return;
                if (viz) viz->compare(static_cast<int>(i), static_cast<int>(i + 1));
                if (arr[i] > arr[i + 1]) { std::swap(arr[i], arr[i + 1]); changed = true; if (viz) viz->swap(static_cast<int>(i), static_cast<int>(i + 1)); }
                if (viz) viz->update(arr);
            }
            if (!changed) break;
            --right;
            for (std::size_t i = right; i > left; --i)
            {
                if (viz && viz->shouldStop()) return;
                if (viz) viz->compare(static_cast<int>(i - 1), static_cast<int>(i));
                if (arr[i - 1] > arr[i]) { std::swap(arr[i - 1], arr[i]); changed = true; if (viz) viz->swap(static_cast<int>(i - 1), static_cast<int>(i)); }
                if (viz) viz->update(arr);
            }
            ++left;
        }
        if (viz) viz->finish();
    }
}