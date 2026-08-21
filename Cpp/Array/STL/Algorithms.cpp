#include <bits/stdc++.h>
using namespace std;

// Pairs
void explainPair(){
    pair<int, int> p = {1, 3};

    cout << "Output of pair p" << endl;
    cout << p.first << " " << p.second << endl;

    pair<int, pair<int, int>> p1 = {1, {3, 4}};
    
    cout << "Output of pair p1" << endl;
    cout << p1.first << " " << p1.second.second << " " << p1.second.first << endl;

    pair<int, int> arr[] = {{1, 2}, {2, 5}, {5, 1}}; // Pair Array
    
    cout << "Output of pair array" << endl;
    for (int i = 0; i < 3; i++){
        cout << arr[i].first << " " << arr[i].second << endl;
    }
}

// Vectors
void explainVector(){

    vector<int> v;
    v.push_back(1);
    v.emplace_back(2);

    vector<pair<int, int>>vec;

    vec.push_back({1, 2});
    vec.emplace_back(1, 2);

    vector<int> vx1(5, 100);

    vector<int> v(5);

    vector<int> v1(5, 20);
    vector<int> v2(v1);

    // Iterator
    vector<int>::iterator it = v.begin();


    // Output of vector
    it++;
    cout << *(it) << " ";

    it = it + 2;
    cout << *(it) << " ";

    // vector<int>::iterator it = v.end();
    // vector<int>::iterator it = v.rend();
    // vector<int>::iterator it = v.rbegin();

    cout << v[0] << " " << v.at(0);
    cout << v.back() << " ";

    for(vector<int>::iterator it = v.begin(); it != v.end(); it++){
        cout << *(it) << " ";
    }

    for (auto it = v.begin(); it != v.end(); it++){
        cout << *(it) << " ";
    }

    for (auto it : v){
        cout << it << " ";
    }


}

// Main func
int main(){
    explainPair();
    return 0;
}