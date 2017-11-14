#include <iostream>
#include <climits>
#include <queue>

#define MAXN 25

using namespace std;

int dist[MAXN][MAXN], minGlobal = INT_MAX;
deque <int> path;

void cpyList(deque <int> R){
    path.clear();
    for(int i = 0; i < R.size(); i++)
        path.push_back(R[i]);
    path.push_back(0);
}

int TSP_BruteForce(deque <int> R, deque <int> S){
    int minCost;
    if(S.empty()){
        minCost = 0;
        for(int i = 0; i < R.size(); i++){
            if(i + 1 < R.size())
                minCost += dist[R[i]][R[i + 1]];
        }
        minCost += dist[R[R.size() - 1]][R[0]];
        if(minGlobal > minCost){
            minGlobal = minCost;
            cpyList(R);
        }
    }else{
        minCost = INT_MAX;
        for(int i = 0; i < S.size(); i++){
            R.push_back(S.front());
            S.pop_front();
            minCost = min(minCost, TSP_BruteForce(R, S));
            S.push_back(R.back());
            R.pop_back();
        }
    }
    return minCost;
}

int main(){
    deque <int> S, R;
    int limit, min;

    cout << "Ingrese el numero de ciudades: ";
    cin >> limit;

    for(int i = 0; i < limit; i++)
        for(int j = 0; j < limit; j++)
            cin >> dist[i][j];
    
    R.push_back(0);
    for(int i = 1; i < limit; i++)
        S.push_back(i);
    
    min = TSP_BruteForce(R, S);

    cout << min << endl;

    for(int i = 0; i < path.size(); i++)
        (i == 0) ? cout << "path { " << path[i] : (i + 1 < path.size()) ? cout << " " << path[i] : cout << " " << path[i] << " }" << endl;

    return 0;
}