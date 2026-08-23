#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;

bool dfs(ll v, vector<int>& color, vector<vector<ll>>& adj, vector<ll>& parent, pair<ll, ll>& p){
    color[v] = 1;
    for(ll u: adj[v]){
        if(color[u] == 0){
            parent[u] = v;
            if(dfs(u, color, adj, parent, p)) return 1;
        } else if(color[u] == 1){
            p.first = v;
            p.second = u;
            return 1;
        }
    }
    color[v] = 2;
    return 0;
}

int main(){
    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> adj(n+1);
    for(ll i = 0; i < m; i++){
        ll a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    pair<ll, ll> p = make_pair(-1, -1);
    vector<int> color(n+1, 0);
    vector<ll> parent(n+1, -1);

    for(ll v = 1; v < n+1; v ++){
        if(color[v] == 0 && dfs(v, color, adj, parent, p)) break;
    }

    if(p.first == -1){
        cout << "IMPOSSIBLE" << endl;
    } else {
        vector<ll> cycle;
        for(ll v = p.first; v != p.second; v = parent[v])
            cycle.push_back(v);
        cycle.push_back(p.second);
        reverse(cycle.begin(), cycle.end());
        cycle.push_back(p.second);

        cout << cycle.size() << endl;
        for(ll x : cycle) cout << x << " ";
        cout << endl;

    }
}