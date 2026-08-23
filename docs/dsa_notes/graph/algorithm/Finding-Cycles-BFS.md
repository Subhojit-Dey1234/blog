Kahn's algorithm works by using BFS and `indegrees` to produce the topological sort of a directed acyclic graph, otherwise a cycle is detected.

A `topological sort` of a directed acyclic graph is a linear ordering of its vertices such that every directed `edge(u, v)` from the vertex u to v, u comes before v

The *indegree* of a vertex is defined the number of edges incident on a vertex in a directed graph

```
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

vector<int> topoSort(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> indegree(n, 0);
    queue<int> q;
    vector<int> list;

    // Compute indegrees
    for (int i = 0; i < n; i++) {
        for (int next : adj[i])
            indegree[next]++;
    }

    // Add all nodes with indegree 0 
    // into the queue
    for (int i = 0; i < n; i++)
        if (indegree[i] == 0)
            q.push(i);

    // Kahn’s Algorithm (BFS)
    while (!q.empty()) {
        int top = q.front();
        q.pop();
        list.push_back(top);
        for (int next : adj[top]) {
            indegree[next]--;
            if (indegree[next] == 0)
                q.push(next);
        }
    }

    return list;
}

void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
}

int main() {
    int n =6;
    vector<vector<int>> adj(n);
    
    addEdge(adj, 0, 1);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 3);
    addEdge(adj, 4, 5);
    addEdge(adj, 5, 1);
    addEdge(adj, 5, 2);

    vector<int> res = topoSort(adj);
    for (int vertex : res)
        cout << vertex << " ";
    cout << endl;
}

```