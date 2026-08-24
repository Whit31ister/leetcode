#include "Sorting.h"
#include "Visualizer/visualizer.h"

#include <algorithm>

namespace Sorting
{
    void counting_sort(std::vector<int>& arr, Visualizer* viz)
    {
        if (arr.empty()) { if (viz) viz->finish(); return; }
        const auto [minimum, maximum] = std::minmax_element(arr.begin(), arr.end());
        const auto range = static_cast<std::size_t>(*maximum - *minimum) + 1;
        std::vector<std::size_t> counts(range);
        for (const int value : arr) ++counts[static_cast<std::size_t>(value - *minimum)];
        std::size_t index = 0;
        for (std::size_t offset = 0; offset < counts.size(); ++offset)
        {
            for (std::size_t count = 0; count < counts[offset]; ++count)
            {
                if (viz && viz->shouldStop()) return;
                arr[index] = static_cast<int>(offset) + *minimum;
                if (viz) viz->update(arr);
                ++index;
            }
        }
        if (viz) viz->finish();
    }
}