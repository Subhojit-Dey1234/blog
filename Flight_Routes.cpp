#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;

struct edge {
    ll node, price;
};

int main(){
    const int MX = 2e5 + 5;
    ll n, m, k;
    cin >> n >> m >> k;
    vector<vector<edge>> gp(MX);
    for(ll i = 0; i < m; i++){
        ll a, b, c;
        cin >> a >> b >> c;
        gp[a].push_back({b, c});
    }
    vector<priority_queue<ll>> bst(MX);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    bst[1].push(0);
    pq.push({0, 1});

    while(!pq.empty()){
        auto f = pq.top();
        pq.pop();

        if(f.first > bst[f.second].top()) continue;
        for(auto nd : gp[f.second]){
            ll tmp = f.first + nd.price;
            if(bst[nd.node].size() < k){
                bst[nd.node].push(tmp);
                pq.push({tmp, nd.node});
            } else if(tmp < bst[nd.node].top()){
                bst[nd.node].pop();
                bst[nd.node].push(tmp);
                pq.push({tmp, nd.node});
            }
       }
    }

    vector<ll> ans;
    while(!bst[n].empty()){
        ll t = bst[n].top();
        bst[n].pop();
        ans.push_back(t);
    }
    reverse(ans.begin(), ans.end());
    for(auto a : ans) cout << a << " ";
    cout << endl;

}