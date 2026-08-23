#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Sorting libraries/sorting_algorithms.hpp"

using namespace std;

template <typename Container>
void print(const Container& values) {
    for (const auto& value : values) {
        cout << value << ' ';
    }
    cout << '\n';
}

void explainPairAndVector() {
    pair<string, int> score = {"Ada", 95};
    cout << "pair: " << score.first << " scored " << score.second << "\n";

    vector<int> values = {10, 20, 30};
    values.push_back(40);
    values.emplace(values.begin() + 1, 15);
    values.erase(values.begin() + 2);
    cout << "vector: ";
    print(values);
    cout << "front/back/size: " << values.front() << '/' << values.back()
         << '/' << values.size() << "\n";
}

void explainContainers() {
    list<int> linked = {3, 1, 2};
    linked.sort();
    deque<string> tasks = {"read", "code"};
    tasks.push_front("plan");

    set<int> ordered = {4, 1, 4, 2};
    unordered_set<string> languages = {"C++", "Java", "Python"};
    map<string, int> inventory = {{"books", 3}, {"pens", 10}};
    unordered_map<string, int> frequency;
    for (int value : {1, 2, 2, 3, 2}) {
        ++frequency[to_string(value)];
    }

    stack<int> undo;
    undo.push(1);
    undo.push(2);
    queue<string> waiting;
    waiting.push("first");
    priority_queue<int> highest_first;
    highest_first.push(7);
    highest_first.push(3);

    cout << "list: ";
    print(linked);
    cout << "deque: ";
    print(tasks);
    cout << "set removes duplicates: ";
    print(ordered);
    cout << "map lookup: " << inventory.at("books") << "\n";
    cout << "stack top / queue front / priority top: " << undo.top() << ' '
         << waiting.front() << ' ' << highest_first.top() << "\n";
    cout << "unordered containers hold " << languages.size() << " languages and "
         << frequency.at("2") << " copies of 2\n";
}

void explainAlgorithms() {
    vector<int> values = {5, 1, 4, 2, 8};
    sort(values.begin(), values.end());
    cout << "std::sort: ";
    print(values);

    reverse(values.begin(), values.end());
    cout << "reverse: ";
    print(values);

    int total = accumulate(values.begin(), values.end(), 0);
    auto first_even = find_if(values.begin(), values.end(), [](int value) {
        return value % 2 == 0;
    });
    cout << "accumulate: " << total << ", first even: " << *first_even << "\n";
}

void explainSortingLibrary() {
    const vector<int> input = {7, 2, 9, 1, 5, 2};
    cout << "\nCustom sorting library (ascending):\n";

    vector<vector<int>> examples(5, input);
    sorting::bubble_sort(examples[0].begin(), examples[0].end());
    sorting::selection_sort(examples[1].begin(), examples[1].end());
    sorting::insertion_sort(examples[2].begin(), examples[2].end());
    sorting::merge_sort(examples[3].begin(), examples[3].end());
    sorting::quick_sort(examples[4].begin(), examples[4].end());

    cout << "bubble / selection / insertion / merge / quick:\n";
    for (const auto& values : examples) {
        print(values);
    }

    vector<int> descending = input;
    sorting::quick_sort(descending.begin(), descending.end(), greater<int>{});
    cout << "quick sort with greater<int>: ";
    print(descending);
}

int main() {
    explainPairAndVector();
    explainContainers();
    explainAlgorithms();
    explainSortingLibrary();
    return 0;
}
