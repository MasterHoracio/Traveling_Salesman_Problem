#include <iostream>
#include <climits>

#define MAXN 25

using namespace std;

int dist[MAXN][MAXN], minGlobal = INT_MAX, minCost, minPath[MAXN];

int min(int a, int b){if(a < b) return a; return b;}

void cpyMinPath(int path[], int size){
    for(int i = 0; i < size; i++)
        minPath[i] = path[i];
}

void swap(int path[],int to, int from){
    int temp = path[to];
    path[to] = path[from];
    path[from] = temp;
}

int TSP_BruteForce(int path[], int l, int lengthSoFar, int size, int minCost){
    if(l == size - 1){
        minCost = lengthSoFar + dist[path[size - 1]][path[0]];
        if(minGlobal > minCost){
            cpyMinPath(path,size);
            minGlobal = minCost;
        }
    }else{
        minCost = INT_MAX;
        for(int i = l + 1; i < size; i++){
            swap(path, l + 1, i);
            int newLenght = lengthSoFar + dist[path[l]][path[l + 1]];
            if(newLenght >= minCost)
                continue;
            else
                minCost = min(minCost, TSP_BruteForce(path, l + 1, newLenght, size, minCost));
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
    
    min = TSP_BruteForce(path, 0, 0, limit, INT_MAX);

    cout << min << endl;
    cout << "{ ";
    for(int i = 0; i < limit; i++)
        (i + 1 < limit) ? cout << minPath[i] << " " : cout << minPath[i] << " " << minPath[0] << " }" << endl;

    return 0;
}