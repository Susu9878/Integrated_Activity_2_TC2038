#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Disjoint {
    vector<int> parent, rank;

    public:
        Disjoint(int n){
            parent.resize(n);
            rank.resize(n);

            for(int i = 0; i < n; i++){
                parent[i] = i;
                rank[i] = i;
            }
        }

        int find(int i){
            return (parent[i] == i) ? i :(parent[i] = find(parent[i]));
        }

        void unite(int x, int y){
            int s1 = find(x), s2 = find(y);
            if(s1 != s2){
                if(rank[s1] < rank[s2])
                    parent[s1] = s2;
                else if(rank[s1] > rank[s2])
                    parent[s2] = s1;
                else 
                    parent[s2] = s1, rank[s1]++;
            }
        }
};

bool compare(vector<int> &a,vector<int> &b){
   return a[2] < b[2]; 
}

vector<vector<int>> Kruskal(int vertices, vector<vector<int>>& matrix){
    Disjoint d(vertices);
    
    vector<vector<int>> mst;

    for (int i = 0; i < matrix.size(); i++) {
        int x = matrix[i][0];
        int y = matrix[i][1];
        int w = matrix[i][2];

        if (d.find(x) != d.find(y)) {
            d.unite(x, y);
            mst.push_back({x, y, w});
            if (mst.size() == vertices - 1) break;
        }
    }

    return mst;
}

#endif