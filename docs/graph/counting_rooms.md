# Counting Rooms

**Problem:** Given a map of a building with rooms (`.`) and walls (`#`), count the number of rooms. Two squares belong to the same room if you can walk from one to the other through open squares, moving up, down, left, or right.

**Constraints:** 1 ≤ n, m ≤ 1000

**Approach:** Treat the grid as a graph where open squares are nodes. For every unvisited open square, run a flood fill (DFS) to mark the whole connected component, and count how many times a fresh flood fill is started.

## Solution — Flood Fill (DFS)

```cpp
#include <iostream>
#include <vector>
#include<unordered_map>
#include<unordered_set>
#include <climits>
#include <algorithm>
#include <string>
#include <set>
#define ll long long
 
using namespace std;

void moveThroughTheRoom(ll i, ll j, vector<vector<char>>& gp){
    if(i < 0 || j < 0 || i >= gp.size() || j >= gp[i].size() || gp[i][j] != '.') return;
    gp[i][j] = '-';
    moveThroughTheRoom(i + 1, j, gp);
    moveThroughTheRoom(i - 1, j, gp);
    moveThroughTheRoom(i , j + 1, gp);
    moveThroughTheRoom(i , j - 1, gp);
}
 
int main(){
    ll n, m;
    cin >> n >> m;

    vector<vector<char>> gp(n, vector<char>(m));
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j ++){
            cin >> gp[i][j];
        }
    }

    ll ans = 0;
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j++){
            if(gp[i][j] == '.'){
                ans ++;
                moveThroughTheRoom(i, j, gp);
            }
        }
    }
    cout << ans << endl;
}
```
