#include <iostream>
#include <vector>
#include <deque>
#include <climits>

#define ll long long

using namespace std;

struct edge {
    ll i;
    ll j;
    ll cost;
};

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

vector<vector<ll>> moveLeft(vector<vector<char>>& gp, ll n, ll m, ll r, ll c) {
    vector<vector<ll>> minLeft(n, vector<ll>(m, LLONG_MAX));
    deque<edge> dq;

    minLeft[r][c] = 0;
    dq.push_back({r, c, 0});

    while (!dq.empty()) {
        edge f = dq.front(); dq.pop_front();
        ll i = f.i, j = f.j, cost = f.cost;

        if (cost > minLeft[i][j]) continue; // stale entry

        for (int d = 0; d < 4; d++) {
            ll x = i + dx[d], y = j + dy[d];
            if (x < 0 || y < 0 || x >= n || y >= m) continue;
            if (gp[x][y] == '*') continue;

            bool isLeftMove = (dx[d] == 0 && dy[d] == -1);
            ll newCost = cost + (isLeftMove ? 1 : 0);

            if (newCost < minLeft[x][y]) {
                minLeft[x][y] = newCost;
                if (isLeftMove) dq.push_back({x, y, newCost});
                else dq.push_front({x, y, newCost});
            }
        }
    }

    return minLeft;
}

vector<vector<ll>> moveRight(vector<vector<char>>& gp, ll n, ll m, ll r, ll c) {
    vector<vector<ll>> minRight(n, vector<ll>(m, LLONG_MAX));
    deque<edge> dq;

    minRight[r][c] = 0;
    dq.push_back({r, c, 0});

    while (!dq.empty()) {
        edge f = dq.front(); dq.pop_front();
        ll i = f.i, j = f.j, cost = f.cost;

        if (cost > minRight[i][j]) continue; // stale entry

        for (int d = 0; d < 4; d++) {
            ll x = i + dx[d], y = j + dy[d];
            if (x < 0 || y < 0 || x >= n || y >= m) continue;
            if (gp[x][y] == '*') continue;

            bool isRightMove = (dx[d] == 0 && dy[d] == 1);
            ll newCost = cost + (isRightMove ? 1 : 0);

            if (newCost < minRight[x][y]) {
                minRight[x][y] = newCost;
                if (isRightMove) dq.push_back({x, y, newCost});
                else dq.push_front({x, y, newCost});
            }
        }
    }

    return minRight;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, r, c;
    cin >> n >> m >> r >> c;

    ll x, y;
    cin >> x >> y;

    vector<vector<char>> gp(n, vector<char>(m));
    for (ll i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (ll j = 0; j < m; j++) {
            gp[i][j] = row[j];
        }
    }

    r--;
    c--;

    vector<vector<ll>> minRight = moveRight(gp, n, m, r, c);
    vector<vector<ll>> minLeft = moveLeft(gp, n, m, r, c);

    ll cnt = 0;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            if (minRight[i][j] <= y && minLeft[i][j] <= x) cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}