#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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

    return 0;
}
