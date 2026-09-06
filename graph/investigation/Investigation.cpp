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

    ll MOD = 1e9 + 7;
    const ll INF = (ll)4e18;

    vector<vector<vector<ll>>> gp(n+1);
    for(ll i = 0; i < m; i++){
        ll a, b, c;
        cin >> a >> b >> c;

        gp[a].push_back({b, c});
    }

    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;

    vector<ll> dst(n+1, INF);
    vector<ll> minCount(n+1, 0);
    vector<ll> maxCount(n+1, 0);
    vector<ll> ways(n+1);

    pq.push(make_pair(0, 1));
    dst[1] = 0;
    ways[1] = 1;

    while(!pq.empty()){
        auto f = pq.top(); pq.pop();
        ll u = f.second, cost = f.first;

        for(auto x : gp[u]){
            ll v = x[0], cst = x[1];
            ll d = cst + cost;
            if(dst[v] > d){
                dst[v] =  dst[u] + cst;
                pq.push(make_pair(dst[v], v));
                ways[v] = ways[u];
                minCount[v] = minCount[u] + 1;
                maxCount[v] = maxCount[u] + 1;
            } else if(dst[v] == d){
                ways[v] = (ways[u] + ways[v])%MOD;
                minCount[v] = min(minCount[v], minCount[u] + 1);
                maxCount[v] = max(maxCount[v], maxCount[u] + 1);
            }
        }
    }

    cout << dst[n] << " " << ways[n] << " " << minCount[n] << " " << maxCount[n] << endl;
}