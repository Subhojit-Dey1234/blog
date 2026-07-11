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

### Dial's algorithm

