The `Floyd-Warshall` algorithm is a method to find the shortest part between the pairs of the nodes in a graph.

The algo works by checking every possible paths between the nodes and the shortest unknown distance between them. 

The `Floyd-Warshall` algorithm can help you figure out the shortest route between any two cities using the all pairs shortest path technique, even if the cities are not directly connected.

![[Pasted image 20260717220215.png]]
### Key Concepts

- **Dynamic Programming** - This method used to solve problems by breaking them into smaller simpler subproblems. In this one, dynamic programming is used to update and keep track of the smallest path between nodes by gradually improving the know distances as more paths are considered.
- **All-Pairs Shortest Paths** : The `Floyd-Warshall` algorithm finds the shortest paths for all pairs of the nodes, `not just return from one node to other`.  Running this will return all possible combination shortest path from one to another
- **Matrix Representation** : Each object represent its distance between two nodes.

### Complexity

**Time Complexity** - O(V^3)
**Space Complexity** - O(V^2)

*V represents the number of vertices in the graph.*

```cpp
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define V 4
#define INF INT_MAX

void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << "   ";
        }
        cout << endl;
    }
}

int main() {
    int graph[V][V] = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };

    floydWarshall(graph);
    return 0;
}
```


