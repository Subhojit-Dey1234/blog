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
