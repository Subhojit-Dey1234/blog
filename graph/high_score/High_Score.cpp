#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;

struct edge
{
    ll src, dest, wt;
};


int main(){
    ll n, m;
    cin >> n >> m;
    
    vector<edge> gp(m);
    for(ll i = 0; i < m; i++){
        cin >> gp[i].src >> gp[i].dest >> gp[i].wt;
    }

    ll NEG = LLONG_MIN / 2;
    vector<ll> dst(n+1, NEG);
    dst[1] = 0;

    // Bellman-Ford
    for(ll i = 0; i < n-1; i++){
        for(ll j = 0; j < m; j++){
            ll u = gp[j].src, v = gp[j].dest, cst = gp[j].wt;
            if(dst[u] != NEG && dst[u] + cst > dst[v]){
                dst[v] = dst[u] + cst;
            }
        }
    }

    vector<bool> infList(n+1, false);
    for(ll j = 0; j < m; j++){
        ll u = gp[j].src, v = gp[j].dest, cst = gp[j].wt;
        if(dst[u] != NEG && dst[u] + cst > dst[v]){
            infList[v] = true;
        }
    }

    for(ll i = 0; i < n-1; i++){
        for(ll j = 0; j < m; j++){
            ll u = gp[j].src, v = gp[j].dest, cst = gp[j].wt;
            if (dst[u] == NEG) continue;
            if (infList[u]) infList[v] = true;
        }
    }

    if(infList[n]) cout << "-1" << endl;
    else cout << dst[n] << endl;
}