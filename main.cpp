#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

//headers
#include "./headers/Maxflow.h"
#include "./headers/Kruskal.h"
#include "./headers/TSP.h"

using namespace std;

int main() {
    int N;
    ifstream inputFile("example.txt"); 
    if(!inputFile.is_open()){
        cerr << "Error: Unable to open file." << endl;
        return 1;
    }

    string line;
    getline(inputFile, line);
    N = stoi(line);

    vector<vector<int>> distance_matrix(N, vector<int>(N));
    vector<vector<int>> flow_matrix(N, vector<int>(N));
    vector<vector<int>> polygons(N, vector<int>(2));

    for(int i = 0; i < N; ++i){
        getline(inputFile, line);
        while (line.empty()) getline(inputFile, line);
        stringstream ss(line);
        for(int j = 0; j < N; ++j){
            ss >> distance_matrix[i][j];
        }
    }

    for(int i = 0; i < N; ++i){
        getline(inputFile, line);
        while (line.empty()) getline(inputFile, line);
        stringstream ss(line);
        for(int j = 0; j < N; ++j){
            ss >> flow_matrix[i][j];
        }
    }

    for(int i = 0; i < N; ++i){
        getline(inputFile, line);
        while (line.empty()) getline(inputFile, line);
        line.erase(remove(line.begin(), line.end(), '('), line.end());
        line.erase(remove(line.begin(), line.end(), ')'), line.end());
        replace(line.begin(), line.end(), ',', ' ');
        stringstream ss(line);
        ss >> polygons[i][0] >> polygons[i][1];
    }
    inputFile.close();

    vector<vector<int>> edges;
    for(int i = 0; i < N; i++) {
        for(int j = i+1; j < N; j++) {
            if(distance_matrix[i][j] != 0) {
                edges.push_back({i, j, distance_matrix[i][j]});
            }
        }
    }

    // sorted edges from smallest to largest
    sort(edges.begin(), edges.end(), compare);

    // Output: 
    cout <<"1. Way of wiring the neighborhoods with fiber" << endl;  //(list of arcs of the form (A,B))
    vector<vector<int>> mst = Kruskal(N, edges);
    for(int i = 0; i<mst.size(); i++){
        cout << "(" << mst[i][0] + 1 << ", " << mst[i][1] + 1 << ")" << endl;
    }

	// 2. route to be followed by the mail delivery personnel
	cout << "2. Shortest route for mail delivery personnel:" << endl;
	TSPResult result = TSP(distance_matrix);

	cout << "   Route: ";
	for (size_t i = 0; i < result.route.size(); ++i) {
    	cout << result.route[i] + 1; // print 1-based index
    	if (i != result.route.size() - 1) cout << " -> ";
	}
	cout << endl;
	cout << "   Total cost: " << result.cost << endl;




    cout << "3. maximum information flow value from the initial node to the final node." << endl;
    cout << CalculateMaxFlow(flow_matrix, N) << endl;
    
    // 4. list of polygons (each element is a list of points of the form (x,y)). 
    //voronoi???
}

/*
for(int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) {
            cout << distance_matrix[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j) {
            cout << flow_matrix[i][j] << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < N; ++i){
        cout << "(" << polygons[i][0] << ", " << polygons[i][1] << ")" << endl;
    }
*/