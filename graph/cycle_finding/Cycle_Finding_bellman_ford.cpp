#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

#define ll long long
using namespace std;

struct edge {
    ll src, dest, len;
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m;
    cin >> n >> m;

    vector<edge> edges(m);
    for (ll i = 0; i < m; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].len;
    }

    vector<ll> dist(n + 1, 0);
    vector<ll> parent(n + 1, -1);
    ll x = -1;

    for(ll i = 0; i < n; i++){
        x = -1;
        for(edge e : edges){
            if(dist[e.src] + e.len < dist[e.dest]){
                dist[e.dest] = dist[e.src] + e.len;
                parent[e.dest] = e.src;
                x = e.dest;
            }
        }
    }

    if(x == -1) cout << "NO" << endl;
    else{
        for(ll i = 0; i < n; i++){
            x = parent[x];
        }

        vector<ll> cycle;
        for(ll v = x;; v = parent[v]){
            cycle.push_back(v);
            if(v == x && cycle.size() > 1) break; 
        }

        reverse(cycle.begin(), cycle.end());
        cout << "YES" << endl;
        for(ll c : cycle) cout << c << " ";
        cout << endl;
    }

    return 0;
}