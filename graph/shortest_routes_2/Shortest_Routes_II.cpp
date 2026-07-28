#include <iostream>
#include<vector>
#include<map>
#include <climits>
#include<algorithm>
#include <queue>

#define ll long long
using namespace std;


// Classic application of Floy-Marshall
int main(){
    ll n, m, q;
    cin >> n >> m >> q;

    vector<vector<ll>> gp(n+1, vector<ll>(n+1, LLONG_MAX));
    for(ll i = 0; i < m; i++){
        ll a, b, w;
        cin >> a >> b >> w;
        gp[a][b] = min(gp[a][b], w);
        gp[b][a] = min(gp[b][a], w);
    }

    vector<vector<ll>> dist(n+1, vector<ll>(n+1, LLONG_MAX));

    for(ll i = 1; i < n+1; i++){
        for(ll j = 1; j < n+1; j++){
            dist[i][j] = gp[i][j];
        }
    }

    for(ll i = 1; i < n+1; i++) dist[i][i] = 0;

    for(ll k = 1; k < n+1; k++){
        for(ll i = 1; i < n+1; i++){
            for(ll j = 1; j < n+1; j++){
                if(dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX && dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    for(ll i = 0; i < q; i++){
        ll x, y;
        cin >> x >> y;

        ll ans = dist[x][y] == LLONG_MAX ? -1 : dist[x][y];

        cout << ans << endl;
    }
}