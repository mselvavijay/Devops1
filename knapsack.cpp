#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the 0/1 Knapsack problem using Dynamic Programming
int knapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Trace selected items
    cout << "Items included in the knapsack:\n";
    int w = capacity;
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i << " (Weight: " << weights[i - 1] << ", Value: " << values[i - 1] << ")\n";
            w -= weights[i - 1];
        }
    }

    return dp[n][capacity];
}

// Function to solve the Fractional Knapsack problem
double fractionalKnapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    vector<pair<double, int>> ratio(n);
    for (int i = 0; i < n; ++i) {
        ratio[i] = { (double)values[i] / weights[i], i };
    }

    sort(ratio.rbegin(), ratio.rend());

    double maxValue = 0.0;

    for (const auto& item : ratio) {
        int idx = item.second;
        if (weights[idx] <= capacity) {
            maxValue += values[idx];
            capacity -= weights[idx];
        } else {
            maxValue += item.first * capacity;
            break;
        }
    }

    return maxValue;
}

// Function to solve the 0/1 Knapsack problem using space optimization
int optimizedKnapsack(int capacity, const vector<int>& weights, const vector<int>& values, int n) {
    vector<int> dp(capacity + 1, 0);

    for (int i = 0; i < n; ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }

    return dp[capacity];
}

int main() {
    int t;
    cout << "Enter the number of test cases: ";
    cin >> t;

    while (t--) {
        int n, capacity;

        cout << "Enter the number of items and the capacity of the knapsack: ";
        cin >> n >> capacity;

        if (capacity <= 0 || n <= 0) {
            cout << "Invalid input. Capacity and number of items must be positive.\n";
            continue;
        }

        vector<int> weights(n), values(n);

        cout << "Enter the weights of the items: ";
        for (int i = 0; i < n; ++i) cin >> weights[i];

        cout << "Enter the values of the items: ";
        for (int i = 0; i < n; ++i) cin >> values[i];

        cout << "\n--- Solving 0/1 Knapsack Problem ---\n";
        int maxValue01 = knapsack(capacity, weights, values, n);
        cout << "Maximum value that can be obtained: " << maxValue01 << endl;

        cout << "\n--- Solving Fractional Knapsack Problem ---\n";
        double maxValueFractional = fractionalKnapsack(capacity, weights, values, n);
        cout << "Maximum value for fractional knapsack: " << maxValueFractional << endl;

        cout << "\n--- Solving Optimized 0/1 Knapsack Problem ---\n";
        int maxValueOptimized = optimizedKnapsack(capacity, weights, values, n);
        cout << "Maximum value with space optimization: " << maxValueOptimized << endl;

        cout << "----------------------------------------\n\n";
    }

    return 0;
}
