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
#define mp make_pair
 
using namespace std;
 
int main(){
    ll n, m;
    cin >> n >> m;
    vector<ll> st = {-1, -1};
    vector<ll> end = {-1, -1};

    vector<vector<char>> gp(n, vector<char>(m));
    vector<vector<bool>> vis(n, vector<bool>(m));

    vector<vector<ll>> pv(n, vector<ll>(m, -1));

    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < m; j ++){
            char c;
            cin >> c;
            if(c == 'A') st = {i, j};
            else if(c == 'B') end = {i, j};

            gp[i][j] = c;
        }
    }

    queue<pair<ll, ll>> q;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};
    string step_dir = "URDL";

    q.push(make_pair(st[0], st[1]));
    vis[st[0]][st[1]] = 1;

    bool found = 0;

    while(!q.empty()){
        auto f = q.front();
        q.pop();

        ll i = f.first, j = f.second;

        if(i == end[0] && j == end[1]){
            found = 1;
            break;
        }

        for(int x = 0; x < 4; x++){
            ll a = dx[x] + i, b = dy[x] + j;
            if(a < 0 || b < 0 || a >= n || b >= m) continue;
            if(vis[a][b]) continue;
            if(gp[a][b] == '#') continue;

            q.push(mp(a, b));
            vis[a][b] = 1;
            pv[a][b] = x;
        }
    }

    if(!found){
        cout << "NO" << endl;
        return 0;
    }

    vector<int> steps;
    while(end != st){
        ll p = pv[end[0]][end[1]];
        steps.push_back(p);
        end = {end[0] - dx[p], end[1] - dy[p]};
    }

    reverse(steps.begin(), steps.end());
    string ans;

    for(int x : steps) ans.push_back(step_dir[x]);

    cout << "YES" << endl;
    cout << ans.size() << endl;
    cout << ans << endl;
}
