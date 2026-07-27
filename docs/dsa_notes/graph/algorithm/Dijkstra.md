Algorithm is popular method to find the **shortest path** in a graph, which can represent things like road and network

It works in both directed and un-directed graphs

⚠️ This algorithm doesn't work for negative edges
	Because it is a greedy approach and it assumes adding a edge can never make a path shorter
### Goal
Goal of the algorithm is to find the quickest or easiest way to get from a starting point to an ending point by checking all the possible routes and choosing the ones with smallest total cost

![Dijkstra shortest path illustration](../../Screenshot%202026-07-10%20at%2012.12.58%20PM.png)


### Dijkstra Algorithm Complexity

`V` represents the number of vertices in the graph
`E` represents the number of edges in the graph

Overall Time complexity - `O((V+E) log V)`
Overall Space complexity - `O(V+E)`

Code in C++

```cpp

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

typedef pair<int, int> iPair;

void dijkstra(vector<vector<iPair>>& graph, int src) {
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    vector<int> dist(graph.size(), INT_MAX);
    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "Vertex Distance from Source\n";
    for (int i = 0; i < graph.size(); ++i)
        cout << i << " \t\t " << dist[i] << endl;
}

int main() {
    int V = 5;
    vector<vector<iPair>> graph(V);

    graph[0].emplace_back(1, 10);
    graph[0].emplace_back(4, 5);
    graph[1].emplace_back(2, 1);
    graph[1].emplace_back(4, 2);
    graph[2].emplace_back(3, 4);
    graph[3].emplace_back(0, 7);
    graph[3].emplace_back(2, 6);
    graph[4].emplace_back(1, 3);
    graph[4].emplace_back(2, 9);
    graph[4].emplace_back(3, 2);

    dijkstra(graph, 0);
    return 0;
}
```

Using priority_queue ( min heap ) helps to allows to extract the vertex with minimum distance in `O(log V)` time 

### What is Bidirectional Dijkstra?

Bidirectional Dijkstra is a variation of Dijkstra’s algorithm that runs two simultaneous searches:

- One search starts from the source and moves forward.
- The other search starts from the target (destination) and moves backward.

Both searches continue until they meet in the middle. The idea behind this approach is that it can significantly reduce the number of vertices and edges explored, especially in large graphs, by halving the search space.


### TODO

#### Print the shortest path

```cpp

#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> dijkstraPath(int n, vector<vector<pair<int, int>>>& adj, int source, int dest) {
    vector<int> dist(n + 1, 1e9);
    vector<int> parent(n + 1);
    for (int i = 1; i <= n; i++) parent[i] = i;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u; // Track predecessor
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    if (dist[dest] == 1e9) return path; // Return empty if path doesn't exist

    int node = dest;
    while (parent[node] != node) {
        path.push_back(node);
        node = parent[node];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());
    
    return path;
}
```


### Problems
 - [Path with Maximum Probability](../problems/L1514.md)
 - [Number of Ways to Arrive at Destination](../problems/L1976.md)