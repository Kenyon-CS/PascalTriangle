#include <iostream>
#include <iomanip>
#include <unordered_map>

// Type alias for a pair of integers
using Pair = std::pair<int, int>;

// Hash function for the unordered_map
struct pair_hash {
    std::size_t operator()(const Pair& p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

// Recursive function to compute binomial coefficients with memoization
unsigned long long binomialCoefficient(int n, int k, std::unordered_map<Pair, unsigned long long, pair_hash>& memo) {
    // Base Cases
    if (k == 0 || k == n)
        return 1;

    Pair key = {n, k};

    // Check if result is already computed
    if (memo.find(key) != memo.end())
        return memo[key];

    // Recursive calculation with memoization
    unsigned long long result = binomialCoefficient(n - 1, k - 1, memo) + binomialCoefficient(n - 1, k, memo);
    memo[key] = result;

    return result;
}

int main() {
    int numRows;

    // Prompt the user for the number of rows
    std::cout << "Enter the number of rows for Pascal's Triangle: ";
    std::cin >> numRows;

    // Input validation
    if (numRows <= 0) {
        std::cerr << "Number of rows must be a positive integer." << std::endl;
        return 1;
    }

    // Memoization map to store computed binomial coefficients
    std::unordered_map<Pair, unsigned long long, pair_hash> memo;

    // Display Pascal's Triangle
    std::cout << "\nPascal's Triangle with " << numRows << " rows:\n" << std::endl;

    for (int n = 0; n < numRows; ++n) {
        // Print leading spaces for alignment
        std::cout << std::setw((numRows - n) * 2) << "";

        for (int k = 0; k <= n; ++k) {
            unsigned long long value = binomialCoefficient(n, k, memo);
            std::cout << std::setw(4) << value;
        }
        std::cout << std::endl;
    }

    return 0;
}
