#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;

bool dfs(ll u, ll par, vector<bool>& vis, vector<vector<ll>>& gp, vector<ll>& cycle, vector<ll>& parent){
    vis[u] = 1;
    for(ll v : gp[u]){
        if(v == par) continue;   // skip the edge back to where we came from

        if(vis[v]){
            cycle = {u, v};
            return true;
        }

        parent[v] = u;
        if(dfs(v, u, vis, gp, cycle, parent)) return true;
    }
    return false;
}

int main(){
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> gp(n+1);
    for(ll i = 1; i < m+1; i++){
        ll x, y;
        cin >> x >> y;
        gp[x].push_back(y);
        gp[y].push_back(x);
    }

    vector<bool> vis(n+1, 0);
    vector<ll> cycle;
    vector<ll> parent(n+1);
    for(ll i = 0; i < n+1; i++) parent[i] = i;

    for(ll i = 1; i < n+1; i++){
        if(!vis[i] && dfs(i, -1, vis, gp, cycle, parent)){
            break;
        }
    }

    if(cycle.empty()) cout << "IMPOSSIBLE" << endl;
    else{
        vector<ll> path;
        for(ll cur = cycle[0]; cur != cycle[1]; cur = parent[cur]){
            path.push_back(cur);
        }
        path.push_back(cycle[1]);
        
        cout << path.size() + 1 << endl;
        for(ll x : path) cout << x << " ";
        cout << cycle[0] << endl;
    }
}