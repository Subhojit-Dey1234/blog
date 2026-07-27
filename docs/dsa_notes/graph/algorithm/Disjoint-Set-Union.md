This one discussed about the `Disjoint Set Union` or `DSU`. Often it is also called `Union Find` because of it two main operations.

This data structure provides the following capabilities. We are given several elements, each of which is a separate set. A `DSU` will have an operation to combine any two sets and it will be able to tell in which set a specific element is. The classic version also introduces a third operation, it can be create a set from a new element.

### Why DSU ?
1. Operation-1: Combine two given sets
2. Operation-2: Tell if two members (b, g) belong to same set or not


Basic interface of this data structure consists of only three operations:
- `make_set(v)` - creates new set consisting of the new element v
- `union_sets(a, b)` - merges the two sets ( the set where a is present and the set where b is present )
- `find_set(v)` - returns the representative of the set that contains the element `v`.  a and b are exactly in same set, if `find_set(a) == find_set(b)` otherwise they are in different sets.

We will store the sets in form of the trees, and root of the tree will be representative / leader of the set. The task is to find the representative of the set of a given element.

## Naive Implementation

The information of all sets are kept in an array named `parent`.

To create a new set ( operation  `make_set(v)`), we simply create a tree with root in the vertex `v` meaning that it is its own ancestor.

To combine two sets ( operation `union_sets(a, b)`), we first find the representative of the set in which `a` is located and representative of set in which `b` is located. If the representatives are identical sets are already merged. 

```cpp
// Without path compression
void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
	// give the leader of the set
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}
```

However this implementation is inefficient. It is easy to construct an example, so that the trees degenerate into long chains. In that case each call `find_set(v)` can take  $O(n)$  time.

```cpp
// With path compression
void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}
```

## Union by size / rank

Here is the implementation of union by size:

```cpp
void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b])
            swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
}
```


Here is the implementation of union by rank based on the depth of the trees:

```cpp

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b]) // the rank of el more will be the parent as more number of elements are pointing
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}
```

 
## Problems

### Detect Cycle using DSU

#### Approach

- Find the parent of all the edges
- If the parent is same then there is a cycle