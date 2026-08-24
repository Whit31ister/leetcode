#include "Sorting.h"
#include "Visualizer/visualizer.h"

#include <utility>

namespace Sorting
{
    namespace
    {
        bool siftDown(std::vector<int>& arr, std::size_t root, const std::size_t end, Visualizer* viz)
        {
            while (root * 2 + 1 <= end)
            {
                if (viz && viz->shouldStop()) return false;
                std::size_t child = root * 2 + 1;
                if (child < end && arr[child] < arr[child + 1]) ++child;
                if (viz) viz->compare(static_cast<int>(root), static_cast<int>(child));
                if (arr[root] >= arr[child]) break;
                std::swap(arr[root], arr[child]);
                if (viz) { viz->swap(static_cast<int>(root), static_cast<int>(child)); viz->update(arr); }
                root = child;
            }
            return true;
        }
    }

    void heap_sort(std::vector<int>& arr, Visualizer* viz)
    {
        if (arr.empty()) { if (viz) viz->finish(); return; }
        for (std::size_t root = arr.size() / 2; root-- > 0;)
        {
            if (!siftDown(arr, root, arr.size() - 1, viz)) return;
        }
        for (std::size_t end = arr.size() - 1; end > 0; --end)
        {
            if (viz && viz->shouldStop()) return;
            std::swap(arr[0], arr[end]);
            if (viz) { viz->swap(0, static_cast<int>(end)); viz->update(arr); }
            if (!siftDown(arr, 0, end - 1, viz)) return;
        }
        if (viz) viz->finish();
    }
}