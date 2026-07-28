#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;

int main(){
    ll n, m;
    cin >> n >> m;

    vector<vector<vector<ll>>> gp(n+1);
    for(ll i = 0; i < m; i++){
        ll x, y, w;
        cin >> x >> y >> w;
        gp[x].push_back({y, w});
        // gp[y].push_back({x, w});
    }

    vector<ll> dist(n+1, LLONG_MAX);
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    pq.push({0, 1});
    dist[1] = 0;

    while(!pq.empty()){
        auto f = pq.top(); pq.pop();
        ll u = f[1];

        if(f[0] > dist[u]) continue;

        for(auto e : gp[u]){
            ll v = e[0], w = e[1];
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    for(ll i = 1; i < n+1; i ++) cout << dist[i] << " ";
    cout << endl;
}