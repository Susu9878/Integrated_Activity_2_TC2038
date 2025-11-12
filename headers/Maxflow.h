#ifndef MAXFLOW_H
#define MAXFLOW_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <string.h>

using namespace std;

bool bfs(vector<vector<int>>& flow_matrix_r, int N, int s, int t, vector<int>& parent)
{
    vector<bool> visited(N, false);
    queue<int> q;
    
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < N; v++) {
            if (visited[v] == false && flow_matrix_r[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
    
    return false;
}

int CalculateMaxFlow(vector<vector<int>> flow_matrix, int N){
    int s = 0; 
    int t = N - 1;

    vector<vector<int>> flow_matrix_r = flow_matrix;
    
    vector<int> parent(N);
    int max_flow = 0; 
    
    while (bfs(flow_matrix_r, s, N, t, parent)) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, flow_matrix_r[u][v]);
        }
        
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            flow_matrix_r[u][v] -= path_flow;
            flow_matrix_r[v][u] += path_flow;
        }
        
        max_flow += path_flow;
    }
    
    return max_flow;
}

#endif
