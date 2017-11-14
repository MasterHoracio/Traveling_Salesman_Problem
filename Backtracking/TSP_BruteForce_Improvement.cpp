#include <iostream>
#include <climits>

#define MAXN 25

using namespace std;

int dist[MAXN][MAXN], minGlobal = INT_MAX, minCost;

int min(int a, int b){if(a < b) return a; return b;}

void swap(int path[],int to, int from){
    int temp = path[to];
    path[to] = path[from];
    path[from] = temp;
}

int TSP_BruteForce(int path[], int l, int lengthSoFar, int size){
    if(l == size - 1){
        minCost = lengthSoFar + dist[path[size - 1]][path[0]];
    }else{
        minCost = INT_MAX;
        for(int i = l + 1; i < size; i++){
            swap(path, l + 1, i);
            int newLenght = lengthSoFar + dist[path[l]][path[l + 1]];
            minCost = min(minCost, TSP_BruteForce(path, l + 1, newLenght, size));
            swap(path, l + 1, i);
        }
    }
    return minCost;
}

int main(){
    int limit, min, path[MAXN];

    cout << "Ingrese el numero de ciudades: ";
    cin >> limit;

    for(int i = 0; i < limit; i++)
        for(int j = 0; j < limit; j++)
            cin >> dist[i][j];

    for(int i = 0; i < limit; i++)
        path[i] = i;
    
    min = TSP_BruteForce(path, 0, 0, limit);

    cout << min << endl;

    return 0;
}