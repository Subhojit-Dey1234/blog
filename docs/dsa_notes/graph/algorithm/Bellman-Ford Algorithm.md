This algorithm is a fundamental algorithm used to find the shortest path in a graph, even when the some of the edges are negative.

### How Bellman-Ford Algorithm Works?

It starts by assuming that the distance from the starting point to all the points is infinite. Except for the starting point that keeping it zero.

The algorithm goes through all the points and tries to update the shortest known distance for each point. It does this for every point, multiple times

A negative weight cycle is a loop in a graph where the total sum of the weights of the edges is negative. If a graph has a negative weight cycle, it means that you could keep going around the cycle, reducing the total path length indefinitely.

If it finds that any edge can still be relaxed (i.e., if a shorter path is still found), it means there is a negative weight cycle in the graph. This is because if there were no negative weight cycles, the shortest paths would have been finalized after V-1 passes. The algorithm then reports the presence of a negative cycle, which indicates that no valid shortest path exists for some nodes.

![Bellman-Ford algorithm illustration](../../Screenshot%202026-07-10%20at%2012.35.46%20PM.png)

```cpp
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(vector<Edge>& edges, int V, int E, int src) {
    vector<int> distance(V, INT_MAX);
    distance[src] = 0;

    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
		        // Find a shorter distance of v going from u
                distance[v] = distance[u] + weight;
            }
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;
        if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
            cout << "Graph contains a negative weight cycle" << endl;
            return;
        }
    }

    cout << "Vertex distances from source:" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << " -> " << distance[i] << endl;
    }
}

int main() {
    int V = 5, E = 8;
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3},
        {1, 3, 2}, {1, 4, 2}, {3, 2, 5},
        {3, 1, 1}, {4, 3, -3}
    };

    bellmanFord(edges, V, E, 0);

    return 0;
}

```


#### Space and Time Complexity

`V` represents the number of vertices in the graph
`E` represents the number of edges in the graph

Overall Time complexity - `O((V*E))`
Overall Space complexity - `O(V+E)`

