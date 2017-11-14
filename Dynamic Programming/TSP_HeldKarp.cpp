#include <bits/stdc++.h>

#define MAXN 55

using namespace std;

typedef struct{
    set <int> sub;
    int curr;
}Index;
typedef struct{
    set <int> st;
}subset;

map <Index, int> minCostDP, parent;
vector <subset> allCombination;
int dist[MAXN][MAXN];

bool operator <(Index const& left, Index const& right){
    if(left.curr < right.curr){
        return true;
    }else if(left.curr > right.curr){
        return false;
    }else{
        if(left.sub.size() < right.sub.size()){
            return true;
        }else if(left.sub.size() > right.sub.size()){
            return false;
        }else{
            set<int>::iterator itone = left.sub.begin();
            set<int>::iterator ittwo = right.sub.begin();
            while(itone != left.sub.end()){
                if(*itone < *ittwo){
                    return true;
                }else if(*itone > *ittwo){
                    return false;
                }
                itone++;
                ittwo++;
            }
        }
    }
}

bool cmp(subset a, subset b){
    if(a.st.size() < b.st.size()){
        return true;
    }else if(a.st.size() > b.st.size()){
        return false;
    }else{
        set<int>::iterator itone = a.st.begin();
        set<int>::iterator ittwo = b.st.begin();
        while(itone != a.st.end()){
            if(*itone < *ittwo){
                return true;
            }else if(*itone > *ittwo){
                return false;
            }
            itone++;
            ittwo++;
        }
    }
}

subset createSubset(int pos, int result[]){
    subset tmp;
    if(pos == 0)
        return tmp;
    for(int i = 0; i < pos; i++)
        tmp.st.insert(result[i]);
    return tmp;
}

void generateAllCombination(int input[], int start, int pos, int result[], int n){
    if(pos == n)
        return;
    subset tmp = createSubset(pos, result);
    allCombination.push_back(tmp);
    for(int i = start; i < n; i++){
        result[pos] = input[i];
        generateAllCombination(input, i + 1, pos + 1, result, n);
    }
}

void generateCombination(int n){
    int *input = new int[n];
    subset tmp;
    for(int i = 0; i < n; i++){
        input[i] = i + 1;
        tmp.st.insert(i + 1);
    }
    int *result = new int[n];
    generateAllCombination(input, 0, 0, result, n);
    allCombination.push_back(tmp);
    sort(allCombination.begin(), allCombination.end(), cmp);
}

int getCost(set<int> tmp, int prevVertex){
    set<int>::iterator it;
    Index indx;

    it = tmp.find(prevVertex);
    tmp.erase(it);

    indx.curr = prevVertex;
    indx.sub = tmp;

    int cost = minCostDP[indx];

    tmp.insert(prevVertex);

    return cost;
}

void HeldKarp(int n){
    int minCost, minPrevVertex, cost, len;
    subset tmp;Index indx;
    
    generateCombination(n - 1);
    len = allCombination.size();

    for(int i = 0; i < len; i++){
        for(int j = 1; j < n; j++){
            tmp = allCombination[i];
            indx.curr = (i + 1 < len) ? j : 0;
            if(tmp.st.find(indx.curr) != tmp.st.end() || (i + 1 == len && j != 1)){
                continue;
            }
            minCost = INT_MAX;
            minPrevVertex = 0;
            indx.sub = tmp.st;
            for(set<int>::iterator it = tmp.st.begin(); it != tmp.st.end(); it++){
                cost = dist[*it][indx.curr] + getCost(tmp.st, *it);
                if(cost < minCost){
                    minCost = cost;
                    minPrevVertex = *it;
                }
            }
            if(tmp.st.size() == 0)
                minCost = dist[0][j];
            minCostDP[indx] = minCost;
            parent[indx] = minPrevVertex;
        }
    }
    
    cout << minCost << endl;
}



int main(){
    int limit, min;
    
    cout << "Ingrese el numero de ciudades: ";
    cin >> limit;

    for(int i = 0; i < limit; i++)
        for(int j = 0; j < limit; j++)
            cin >> dist[i][j];
    
    HeldKarp(limit);

    return 0;
}