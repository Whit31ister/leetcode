#include "Sorting.h"
#include "Visualizer/visualizer.h"
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
    Sorting::Visualizer viz(1600, 1000, 90);
    std::size_t arraySize = 40;
    int delayMilliseconds = 40;
    int minValue = 10;
    int maxValue = 189;
    bool randomizeSize = false;
    bool soundEnabled = true;
    int chooseSort = viz.selectAlgorithm(arraySize, delayMilliseconds, minValue, maxValue, randomizeSize, soundEnabled);
    std::mt19937 sizeEngine(std::random_device{}());
    std::uniform_int_distribution<std::size_t> sizeDistribution(10, 200);
    while (viz.isOpen() && chooseSort != 0)
    {
        viz.setDelay(delayMilliseconds);
        viz.setSoundEnabled(soundEnabled);
        const std::size_t generatedSize = randomizeSize
            ? sizeDistribution(sizeEngine)
            : arraySize;
        std::vector<int> originalValues = generateRandomVector(generatedSize, minValue, maxValue);
        std::vector<int> values = originalValues;
        viz.resetStatistics();
        
        switch (chooseSort)
        {
        case 1:
            Sorting::insertion_sort(values, &viz);
            break;
        case 2:
            Sorting::selection_sort(values, &viz);
            break;
        case 3:
            Sorting::bubble_sort(values, &viz);
            break;
        case 4:
            Sorting::merge_sort(values, &viz);
            break;
        case 5:
            Sorting::quick_sort(values, &viz);
            break;
        case 6:
            Sorting::shell_sort(values, &viz);
            break;
        case 7:
            Sorting::heap_sort(values, &viz);
            break;
        case 8:
            Sorting::counting_sort(values, &viz);
            break;
        case 9:
            Sorting::cocktail_sort(values, &viz);
            break;
        case 10:
            Sorting::comb_sort(values, &viz);
            break;
        }
        
        if (viz.consumeRandomizeRequest())
        {
            const std::size_t generatedSize = randomizeSize
                ? sizeDistribution(sizeEngine)
                : arraySize;
            originalValues = generateRandomVector(generatedSize, minValue, maxValue);
            values = originalValues;
        }
        else if (viz.consumeRestartRequest())
        {
            values = originalValues;
        }
        else if (viz.consumeBackRequest())
        {
            chooseSort = viz.selectAlgorithm(arraySize, delayMilliseconds, minValue, maxValue, randomizeSize, soundEnabled);
        }
        else
        {
            break;
        }
    }

    return 0;
}
