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

    vector<int> ans(n+1, -1);


    for(ll i = 1; i < n+1; i++){
        if(ans[i] != -1) continue;
        queue<ll> q;
        q.push(i);
        ans[i] = 1;

        while(!q.empty()){
            ll f = q.front(); q.pop();

            for(ll x : gp[f]){
                if(ans[x] == ans[f]){
                    cout << "IMPOSSIBLE" << endl;
                    return 0;
                }
                if(ans[x] != -1) continue;
                ans[x] = 3 - ans[f];
                q.push(x);
            }
        }
    }

    for(ll i = 1; i < n+1; i++) cout << ans[i] << " ";
    cout << endl;
}