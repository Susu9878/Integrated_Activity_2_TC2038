#ifndef MAXFLOW_H
#define MAXFLOW_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <string.h>

using namespace std;
bool bfs(vector<vector<int>> flow_matrix_r, int N,  int s, int t, int parent[])
{
    bool visited[N];
    memset(visited, 0, sizeof(visited));

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int n = 0; n < N; n++) {
            if (visited[n] == false && flow_matrix_r[u][n] > 0) {

                if (n == t) {
                    parent[n] = u;
                    return true;
                }
                q.push(n);
                parent[n] = u;
                visited[n] = true;
            }
        }
    }
    return false;
}

int CalculateMaxFlow(vector<vector<int>> flow_matrix, int N)
{
    // int s - start point
    // int t - end point
    int s,t,u,n;
    vector<vector<int>> flow_matrix_r;

    for (u = 0; u < N; u++)
        for (n = 0; n < N; n++)
            flow_matrix_r[u][n] = flow_matrix[u][n];

    int parent[N]; 

    int max_flow = 0; 


    while (bfs(flow_matrix_r, N ,s, t, parent)) {

        int path_flow = INT_MAX;
        for (n = t; n != s; n = parent[n]) {
            u = parent[n];
            path_flow = min(path_flow, flow_matrix_r[u][n]);
        }


        for (n = t; n != s; n = parent[n]) {
            u = parent[n];
            flow_matrix_r[u][n] -= path_flow;
            flow_matrix_r[n][u] += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}


#endif
