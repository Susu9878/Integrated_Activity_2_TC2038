#ifndef TSP_H
#define TSP_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits>
#include <string>
using namespace std;

struct TSPResult {
    vector<int> route;
    int cost;
};


inline TSPResult TSP(vector<vector<int>>& matrix) {
    int n = matrix.size();
    const int INF = numeric_limits<int>::max() / 4;
    const int START = 0;
    const int FULL = (1 << n);

    vector<vector<int>> dp(FULL, vector<int>(n, INF));
    vector<vector<int>> parent(FULL, vector<int>(n, -1));
    dp[1 << START][START] = 0;

    for (int mask = 0; mask < FULL; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                int nextMask = mask | (1 << v);
                int newCost = dp[mask][u] + matrix[u][v];
                if (newCost < dp[nextMask][v]) {
                    dp[nextMask][v] = newCost;
                    parent[nextMask][v] = u;
                }
            }
        }
    }

    // Close the cycle back to start
    int bestCost = INF;
    int lastCity = -1;
    for (int i = 1; i < n; i++) {
        int cost = dp[FULL - 1][i] + matrix[i][START];
        if (cost < bestCost) {
            bestCost = cost;
            lastCity = i;
        }
    }

    vector<int> route;
    int mask = FULL - 1;
    int cur = lastCity;
    while (cur != -1) {
        route.push_back(cur);
        int prev = parent[mask][cur];
        mask ^= (1 << cur);
        cur = prev;
    }
    reverse(route.begin(), route.end());
    route.push_back(START); // return to start

    return {route, bestCost};
}

#endif
