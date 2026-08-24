#include "Sorting.h"
#include "visualizer.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>

namespace
{
    std::vector<int> generateRandomVector(const std::size_t size, const int minValue, const int maxValue)
    {
        std::vector<int> values(size);
        std::iota(values.begin(), values.end(), minValue);

        std::random_device device;
        std::mt19937 engine(device());
        std::shuffle(values.begin(), values.end(), engine);

        for (int& value : values)
        {
            value = std::clamp(value, minValue, maxValue);
        }

        return values;
    }
} // namespace


int main()
{
    std::vector<int> originalValues = generateRandomVector(40, 10, 189);
    std::vector<int> values = originalValues;

    Sorting::Visualizer viz(1200, 800, 90);
    viz.setDelay(40);

    while (viz.isOpen())
    {
        viz.resetStatistics();
        Sorting::merge_sort(values, &viz);

        if (viz.consumeRandomizeRequest())
        {
            originalValues = generateRandomVector(180, 10, 189);
            values = originalValues;
        }
        else if (viz.consumeRestartRequest())
        {
            values = originalValues;
        }
        else
        {
            break;
        }
    }

    return 0;
}
