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
    vector<ll> dp(n+1, -1);
    vector<ll> parent(n+1, -1);
    dp[1] = 1;
    parent[1] = 1;
    for(ll t : topo){
        if(dp[t] == -1) continue; 
        for(ll x : gp[t]){
            if(dp[t] + 1 > dp[x]){
                dp[x] = dp[t] + 1;
                parent[x] = t;
            }
        }
    }

    if(dp[n] == -1){
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    vector<ll> path;
    cout << dp[n] << endl;

    ll x = n;
    while(parent[x] != x){
        path.push_back(x);
        x = parent[x];
    }

    path.push_back(1);
    reverse(path.begin(), path.end());

    for(ll p : path) cout << p << " ";
    cout << endl;
}