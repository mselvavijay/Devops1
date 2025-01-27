#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
int knapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    // Create a DP table where dp[i][w] represents the maximum value that can be obtained
    // with the first i items and capacity w.
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    // Build the DP table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            // If the weight of the current item is less than or equal to the capacity
            if (weights[i - 1] <= w) {
                // Take the maximum of including or excluding the current item
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                // If the current item can't be included, just exclude it
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right cell contains the maximum value that can be obtained
    return dp[n][capacity];
}

int main() {
    int n, capacity;
    
    // Input the number of items and the knapsack capacity
    cout << "Enter the number of items and the capacity of the knapsack: ";
    cin >> n >> capacity;

    vector<int> weights(n), values(n);

    // Input the weights and values of the items
    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> values[i];
    }

    // Solve the knapsack problem
    int result = knapsack(capacity, weights, values, n);

    // Output the result
    cout << "Maximum value that can be obtained: " << result << endl;

    return 0;
}
