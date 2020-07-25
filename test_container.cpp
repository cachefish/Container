#include"Vector.h"
#include<iostream>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;
using namespace cc;

void vector_test()
{
     std::vector<int> v;
    v.insert(v.begin(), 11);
    v.push_back(3);
    v.pop_back();
    v.push_back(4);
    v.emplace(v.begin(),888);
    v.insert(v.begin()+2,6);
    v.insert(v.begin()+1,7);
    v.push_back(8);
    v.insert(v.end(), 1);
    v.insert(v.begin()+2, 2);
    v.pop_back();
    v.push_back(9);
    v.pop_back();
    v.push_back(10);
    v.push_back(1);
    v.push_back(3);
    v.insert(v.begin()+1, 2);

    cc::Vector<int> vec;
    vec.insert(vec.begin(), 11);
    vec.push_back(3);
    vec.pop_back();
    vec.push_back(4);
    vec.emplace(vec.begin(),888);
    vec.insert(vec.begin()+2,6);
    vec.insert(vec.begin()+1,7);
    vec.push_back(8);
    vec.insert(vec.end(), 1);
    vec.insert(vec.begin()+2, 2);
    vec.pop_back();
    vec.push_back(9);
    vec.pop_back();
    vec.push_back(10);
    vec.push_back(1);
    vec.push_back(3);
    vec.insert(vec.begin()+1, 2);

    for (int j = 0; j < v.size(); ++j) {
        std::cout << v[j] << " ";
    }
    std::cout << std::endl;
    for (int j = 0; j < v.size(); ++j) {
        std::cout << vec[j] << " ";
    }

    cc::Vector<int> temp(v.begin(), v.end());
    assert(temp == vec);

    cout << endl;
}

int main()
{
    vector_test();
    return 0;
}