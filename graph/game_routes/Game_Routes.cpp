#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;
ll MOD = 1e9+7;

int main(){
    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> gp(n+1);
    vector<ll> indeg(n+1, 0);

    for(ll i = 0; i < m; i ++){
        ll a, b;
        cin >> a >> b;
        gp[a].push_back(b);
        indeg[b] ++;
    }

    queue<ll> q;
    for(ll i = 1; i <= n; i++){
        if(indeg[i] == 0) q.push(i);
    }

    vector<ll> topo;
    while(!q.empty()){
        ll f = q.front();
        q.pop();
        topo.push_back(f);

        for(ll v : gp[f]){
            indeg[v] --;
            if(indeg[v] == 0) q.push(v);
        }
    }


    vector<ll> ways(n+1);
    ways[1] = 1;
    for(ll u : topo){
        for(ll v : gp[u]){
            ways[v] = (ways[u] + ways[v])%MOD;
        }
    }

    cout << ways[n] << endl;
}