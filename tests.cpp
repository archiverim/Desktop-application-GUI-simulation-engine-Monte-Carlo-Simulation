// tests.cpp
#include <iostream>
#include <cassert>
#include "lotto.h" 
using namespace std;



void testCombination() {
    assert(combination(49, 6) == 13983816);  // known value
    assert(combination(6, 6) == 1);
    assert(combination(10, 2) == 45);
    cout << "combination() tests passed\n";
}

void testCountMatches() {
    vector<int> a = {1, 2, 3, 4, 5, 6};
    vector<int> b = {1, 2, 3, 7, 8, 9};
    assert(countMatches(a, b) == 3);

    vector<int> c = {10, 11, 12, 13, 14, 15};
    assert(countMatches(a, c) == 0);

    assert(countMatches(a, a) == 6);
    cout << "countMatches() tests passed\n";
}

int main() {
    testCombination();
    testCountMatches();
    cout << "All tests passed.\n";
    return 0;
}