Using BFS, we can found the shortest paths between single source and other vertices in `O(E)`in an unweighted graph.

 If not all edges in graph have the same weight, then we need a more general algorithm, like `Dijkstra` which runs in  $O(|V|^2 + |E|)$  or  $O(|E| \log |V|)$  time.

But we can optimise that algorithm with weights `0 or 1` to solve `single source shortest path`  in the problem `O(E)`

Because of the zero-one weights, the difference between the distances between the source `s` and two other vertices in the queue differs by at most one.

```
d[v] <= d[u] <= d[v] + 1
```

The reason for this is, that we only add vertices with equal distance or with distance plus one to the queue during each iteration.

Assuming there exists a  $u$  in the queue with  $d[u] - d[v] > 1$ , then  $u$  must have been inserted into the queue via a different vertex  $t$  with  $d[t] \ge d[u] - 1 > d[v]$
However this is impossible, since Dijkstra's algorithm iterates over the vertices in increasing order.
 $$Q = \underbrace{v}_{d[v]}, \dots, \underbrace{u}_{d[v]}, \underbrace{m}_{d[v]+1} \dots \underbrace{n}_{d[v]+1}$$

The structure is simple if the weight is zero then add to the start and if it is one then at the end.
This will ensure the queue is always sorted

```cpp
if(w == 0){
	dst[v] = dst[u];
	dq.push_front(v);
}
else if(w == 1){
	dst[v] = dst[u] + 1;
	dq.push_back(v);
}
```


Solutions of 0-1 BFS

```cpp

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
```

### Problem: Minimum Cost to Make at Least One Valid Path in a Grid (LeetCode 1368)

> Given an `m x n` grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of `grid[i][j]` can be:
>
> - `1` which means go to the cell to the right. (i.e go from `grid[i][j]` to `grid[i][j + 1]`)
> - `2` which means go to the cell to the left. (i.e go from `grid[i][j]` to `grid[i][j - 1]`)
> - `3` which means go to the lower cell. (i.e go from `grid[i][j]` to `grid[i + 1][j]`)
> - `4` which means go to the upper cell. (i.e go from `grid[i][j]` to `grid[i - 1][j]`)
>
> Notice that there could be some signs on the cells of the grid that point outside the grid.
>
> You will initially start at the upper left cell `(0, 0)`. A valid path in the grid is a path that starts from the upper left cell `(0, 0)` and ends at the bottom-right cell `(m - 1, n - 1)` following the signs on the grid. The valid path does not have to be the shortest.
>
> You can modify the sign on a cell with `cost = 1`. You can modify the sign on a cell one time only.
>
> Return the minimum cost to make the grid have at least one valid path.

#### Reasoning

Every cell has exactly one sign, and that sign is really just an edge to one of its 4 neighbours that we can walk for free (cost `0`). The other 3 neighbours are also reachable from that cell, but only by overwriting the sign, which costs `1`.

So each cell fans out into 4 directed edges to its neighbours:
- the edge matching the current sign has weight `0`
- the other 3 edges have weight `1`

That turns the problem into a single-source shortest path from `(0, 0)` to `(n-1, m-1)` on a graph whose edges only weigh `0` or `1` — exactly the 0-1 BFS setup: push the free (matching-sign) move to the **front** of the deque so it's explored before any move that cost something, and push the costly moves to the **back**.

Since `dx/dy` are ordered `right, left, down, up`, the index `id` of a direction (`0..3`) lines up with the sign values `1..4` (`id + 1 == grid[i][j]`), which is what `matchesSign` checks.

#### Solution

```cpp
struct edge {
    int i;
    int j;
    int cost;
};

class Solution {
public:
    vector<vector<int>> move(vector<vector<int>>& grid, int n, int m, vector<int>& dx, vector<int>& dy){
        vector<vector<int>> cost(n, vector<int>(m, INT_MAX));

        deque<edge> dq;
        dq.push_back({0, 0, 0});
        cost[0][0] = 0;

        while(!dq.empty()){
            edge f = dq.front(); dq.pop_front();
            int i = f.i;
            int j = f.j;
            int cst = f.cost;

            for(int id = 0; id < 4; id ++){
                int x = dx[id] + i;
                int y = dy[id] + j;
                if(x < 0 || y < 0 || x >= n || y >= m) continue;

                bool matchesSign = (grid[i][j] == (id + 1));
                int newCost = cst + (matchesSign ? 0 : 1);

                if(newCost < cost[x][y]){
                    cost[x][y] = newCost;
                    if(matchesSign) dq.push_front({x, y, newCost});
                    else dq.push_back({x, y, newCost});
                }
            }
        }

        return cost;
    }
    int minCost(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<int> dx = {0, 0, 1, -1};
        vector<int> dy = {1, -1, 0, 0};
        vector<vector<int>> cost = move(grid, n, m, dx, dy);
        return cost[n-1][m-1];
    }
};
```

### Dial's Algorithm

0-1 BFS works because with only two edge weights (`0` and `1`), a vertex's distance is always either equal to the current front-of-deque distance or exactly one more — so a plain deque is enough to keep vertices sorted by distance.

Dial's algorithm generalises this to edge weights that are small non-negative integers bounded by some constant `W`. Instead of one deque, keep an array of buckets `bucket[0..W*V]`, where `bucket[d]` holds every vertex currently known to be at distance `d` from the source. Process buckets in increasing order of `d`; popping a vertex from `bucket[d]` and relaxing its edges can only push neighbours into buckets `>= d`, so once `bucket[d]` is drained, distance `d` is finalised for every vertex in it — same idea as a priority queue, but with `O(1)` insert/extract instead of `O(log V)`.

0-1 BFS is just Dial's algorithm with `W = 1`: only two buckets are ever "live" at once (current distance and current + 1), so a two-ended deque replaces the bucket array.

```cpp
void dial(vector<vector<pair<int,int>>>& graph, int src, int W) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<vector<int>> bucket(W * (n - 1) + 1); // max possible distance is W*(n-1)

    dist[src] = 0;
    bucket[0].push_back(src);

    for (int d = 0; d < (int)bucket.size(); d++) {
        while (!bucket[d].empty()) {
            int u = bucket[d].back();
            bucket[d].pop_back();
            if (dist[u] != d) continue; // stale entry, already relaxed via a shorter path

            for (auto& [v, w] : graph[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    bucket[dist[v]].push_back(v);
                }
            }
        }
    }
}
```

