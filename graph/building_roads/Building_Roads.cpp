#include <iostream>
#include <vector>
#include<unordered_map>
#include<unordered_set>
#include <climits>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
#define ll long long
 
using namespace std;
 
int main(){
    ll n, m;
    cin >> n >> m;
    vector<bool> vis(n+1, 0);
    vector<vector<ll>> gp(n+1);

    for(ll i = 0; i < m; i++){
        ll a, b;
        cin >> a >> b;
        gp[a].push_back(b);
        gp[b].push_back(a);
    }

    int k = 0;
    ll lst = -1;

    vector<vector<ll>> rd;

    for(ll i = 1; i < n+1; i++){
        if(vis[i]) continue;

        queue<ll> q;
        q.push(i);
        vis[i] = 1;
        k ++;

        if(lst > 0){
            rd.push_back({lst, i});
        }
        
        while(!q.empty()){
            ll f = q.front();
            q.pop();
            lst = f;

            for(ll x : gp[f]){
                if(vis[x]) continue;
                vis[x] = 1;
                q.push(x);
            }
        }
    }
    if(k <= 1){
        cout << 0 << endl;
        return 0;
    }

    cout << k-1 << endl;

    for(auto x : rd){
        cout << x[0] << " " << x[1] << endl;
    }

}
