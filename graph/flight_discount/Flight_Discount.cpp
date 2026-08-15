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
        ll u, v, w;
        cin >> u >> v >> w;
        gp[u].push_back({v, w});
    }

    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    pq.push({0, 1, 0});

    vector<vector<ll>> dst(n+1, vector<ll>(2, LLONG_MAX));

    while(!pq.empty()){
        auto f = pq.top(); pq.pop();
        ll cst = f[0], u = f[1], discount = f[2];
        if(cst > dst[u][discount]) continue;

        for(auto x : gp[u]){
            ll v = x[0], c = x[1];
            if(discount == 0){
                ll cost = cst + c;
                if(dst[v][0] > cost){
                    pq.push({cost, v, 0});
                    dst[v][0] = cost;
                }

                ll cost1 = cst + (c / 2);
                if(dst[v][1] > cost1){
                    pq.push({cost1, v, 1});
                    dst[v][1] = cost1;
                }
            }else{
                ll cost = c + cst;
                if(dst[v][1] > cost){
                    pq.push({cost, v, 1});
                    dst[v][1] = cost;
                }
            }
        }
    }

    cout << dst[n][1] << endl;
}