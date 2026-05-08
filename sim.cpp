#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <map>
#include <numeric> // for iota
#include <set>
#include <chrono>

using namespace std;

long long combination(int n, int k);
vector<int> generateDraw();
int countMatches(const vector<int>& a, const vector<int>& b);

int main() {
    cout << "Welcome to Lotto 6/49 Simulation" << endl;

    // User input
    vector<int> userNums(6);
    cout << "Enter your 6 numbers (between 1 and 49): ";
    for (int i = 0; i < 6; i++) {
        cin >> userNums[i];
    }

    // Probability
    long long total = combination(49, 6);
    double probability = 1.0 / total;
    cout << "Probability of winning jackpot: " << probability << endl;

    // Prize tiers
    map<int, double> prize = {
        {6, 5000000},
        {5, 5000},
        {4, 100},
        {3, 10}
    };

    // Simulation
    int simulations = 100000;
    
    auto start = chrono::high_resolution_clock::now();
    
    map<int, int> results;
    
    for (int i = 0; i < simulations; i++) {
        vector<int> draw = generateDraw();
        int match = countMatches(userNums, draw);
        results[match]++;
    }
    
    auto end = chrono::high_resolution_clock::now();
    cout << "\nExecution time: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;

    cout << "\nProbability per match:\n";
    for (auto& [matches, count] : results) {
        double prob = (double)count / simulations;
        cout << matches << " matches: " << prob << endl;
    }

    // Print results
    cout << "\nMatch Distribution:\n";
    for (auto& [matches, count] : results) {
        cout << matches << " matches: " << count << endl;
    }

    // Expected value
    double totalReturn = 0;

    for (auto& [matches, count] : results) {
        if (prize.count(matches)) {
            totalReturn += count * prize[matches];
        }
    }

    double expectedValue = totalReturn / simulations;
    cout << "\nExpected value per ticket: $" << expectedValue << endl;

    return 0;
}

// Combination function
long long combination(int n, int k) {
    long long result = 1;
    for (int i = 1; i <= k; i++)
        result = result * (n - k + i) / i;
    return result;
}

// Generate random draw
vector<int> generateDraw() {
    vector<int> nums(49);
    iota(nums.begin(), nums.end(), 1);
    shuffle(nums.begin(), nums.end(), default_random_engine(random_device{}()));
    return vector<int>(nums.begin(), nums.begin() + 6);
}

// Count matches
int countMatches(const vector<int>& a, const vector<int>& b) {
    set<int> s(b.begin(), b.end());
    int count = 0;
    for (int x : a)
        if (s.count(x)) count++;
    return count;
}