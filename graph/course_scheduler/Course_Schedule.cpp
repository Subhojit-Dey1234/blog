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
    vector<ll> indegree(n+1, 0);
    for(ll i = 0; i < m; i++){
        ll a, b;
        cin >> a >> b;
        gp[a].push_back(b);
        indegree[b] ++;
    }

    queue<ll> q;
    for(ll i = 1; i < n+1; i++) if(indegree[i] == 0) q.push(i);

    vector<ll> lst;
    while(!q.empty()){
        int u = q.front(); q.pop();
        lst.push_back(u);

        for(int v : gp[u]){
            indegree[v] --;
            if(indegree[v] == 0){
                q.push(v);
            }
        }
    }

    if(lst.size() != n) cout << "IMPOSSIBLE" << endl;
    else{
        for(ll x : lst) cout << x << " ";
        cout << endl;
    }

}