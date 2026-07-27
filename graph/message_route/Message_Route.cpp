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

    vector<vector<ll>> gp(n+1);
    for(ll i = 0; i < m; i++){
        ll x, y;
        cin >> x >> y;
        gp[x].push_back(y);
        gp[y].push_back(x);
    }

    vector<ll> dist(n+1, LLONG_MAX);
    vector<ll> parent(n+1);
    for(ll i = 1; i < n+1; i++) parent[i] = i;

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll,ll>>> pq;
    pq.push(make_pair(1, 1));
    dist[1] = 1;

    while(!pq.empty()){
        auto f = pq.top(); pq.pop();
        ll u = f.second;

        for(ll v : gp[u]){
            if(dist[v] <= dist[u] + 1) continue;

            dist[v] = dist[u] + 1;
            parent[v] = u;
            pq.push(make_pair(dist[v],v));
        }
    }

    if(dist[n] == LLONG_MAX){
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<ll> path;
    ll nd = n;
    while(parent[nd] != nd){
        path.push_back(nd);
        nd = parent[nd];
    }
    path.push_back(1);
    reverse(path.begin(), path.end());

    cout << path.size() << endl;
    for(ll p : path) cout << p << " ";
    cout << endl;

}