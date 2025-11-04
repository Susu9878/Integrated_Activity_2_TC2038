#include <vector>
#include <iostream>

using namespace std;

int main(){
    int N;
    cin >> N;

    vector<vector<int>> distance_matrix(N, vector<int>(N));
    vector<vector<int>> flow_matrix(N, vector<int>(N));

    int d;
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> d;
            distance_matrix[i][j] = d;
        }
    }
    for(int i = 0; i<N; i++){
        for(int j = 0; j<N; j++){
            cin >> d;
            flow_matrix[i][j] = d;
        }
    }
    cout << endl;
}

/*
for(int i = 0; i<N; i++){
    for(int j = 0; j<N; j++){
        cout << distance_matrix[i][j] << " ";
    }
    cout << endl;
}
for(int i = 0; i<N; i++){
    for(int j = 0; j<N; j++){
        cout << flow_matrix[i][j] << " ";
    }
    cout << endl;
}
*/