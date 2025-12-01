#ifndef MAXFLOW_H
#define MAXFLOW_H

#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

bool bfs(vector<vector<int>>& residual, int s, int t, int parent[], int N) {
    vector<bool> visited(N, false);

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while(!q.empty()) {
        int u = q.front();
        q.pop();

        for(int v = 0; v < N; v++) {
            if (!visited[v] && residual[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);

                if (v == t)
                    return true;
            }
        }
    }

    return false;
}

int maxFlow(vector<vector<int>>& graph, int s, int t, int N) {

    vector<vector<int>> residual = graph;
    vector<int> parent(N);
    int max_flow = 0;

    while(bfs(residual, s, t, parent.data(), N)) {
        int path_flow = INT_MAX;

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, residual[u][v]);
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= path_flow;
            residual[v][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

#endif
