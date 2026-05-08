// lotto.h
#pragma once
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <random>
using namespace std;

inline long long combination(int n, int k) {
    long long result = 1;
    for (int i = 1; i <= k; i++)
        result = result * (n - k + i) / i;
    return result;
}

inline vector<int> generateDraw() {
    vector<int> nums(49);
    iota(nums.begin(), nums.end(), 1);
    shuffle(nums.begin(), nums.end(), default_random_engine(random_device{}()));
    return vector<int>(nums.begin(), nums.begin() + 6);
}

inline int countMatches(const vector<int>& a, const vector<int>& b) {
    set<int> s(b.begin(), b.end());
    int count = 0;
    for (int x : a)
        if (s.count(x)) count++;
    return count;
}