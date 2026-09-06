A Segment Tree is a data structure that stores information about array intervals as a tree. This allows answering range queries over an array efficient. This includes finding the sum of the consecutive array elements `a[l...r]` or finding the minimum element in such range in `O(logn)` time.

### Simplest form of a Segment Tree

To start easy, we consider the simplest form of a Segment Tree. We want to answer sum queries efficiently. The formal definition of our task is:

Give an array `a[0...n-1]`, the Segment Tree must be able to find the sum of the elements the indices `l` and `r` and also handle changing values of the element in the array. The Segment Tree should be able to process the query in `O(log N)` time.

### Structure of the Segment Tree

We can take a divide and conquer approach when it comes to array segment. We compute and store the sum of the elements of the whole array, i.e. the sum of the segment `a[0...n-1]` 

We then spilt the array into two halves $a[0...(n-1)/2]$ and $a[(n+1)/2...(n-1)]$ and compute the sum of each halve and store them. Each of these two halves in turn are split in half and so on until all the segments reach size 1.

Here is a visual representation of such a Segment Tree over the array  $a = [1, 3, -2, 8, -7]$ :

![[Screenshot 2026-08-30 at 11.07.01 AM.png]]

It is worth noting that whenever  $n$  is not a power of two, not all levels of the Segment Tree will be completely filled. We can see that behavior in the image. For now we can forget about this fact, but it will become important later during the implementation.

The height of the Segment Tree is `O(log n)`

### Construction

Before constructing the segment tree, we need to decide:
1. The `value`that gets stored at each node of the segment tree. For example, in a sum segment tree, a node would store the sum of the elements in its range `[l, r]`
2. The `merge` operation merges two siblings in a segment tree. For example, the two nodes corresponding to the ranges `a[l1...r1]` and `a[l2...r2]` would be merged into node corresponding to the range `a[l1...r2]`.

The leaf is called leaf vertex if its corresponding segment covers only one one value in the original array.

### Sum Queries

For now we are going to answer sum queries. As an input we receive two integers  $l$  and  $r$ , and we have to compute the sum of the segment  $a[l \dots r]$  in  $O(\log n)$  time.

To do this, we will traverse the Segment Tree and use the precomputed sums of the segments. 

The calculation of the query is a traversal of the tree, which spreads through all necessary branches of the tree, and uses the precomputed sum values of the segments in the tree.

### Implementation

The main consideration is how to store the Segment Tree. Of course we can define $Vertex$ struct and create objects, that store the boundaries of the segment, its sum and additionally also pointers to its child vertices.

 The sum of the root vertex at index 1, the sums of its two child vertices at indices 2 and 3, the sums of the children of those two vertices at indices 4 to 7, and so on. With 1-indexing, conveniently the left child of a vertex at index  $i$  is stored at index  $2i$ , and the right one at index  $2i + 1$ . Equivalently, the parent of a vertex at index  $i$  is stored at  $i/2$  (integer division).

So, we store the Segment Tree simply as an array  $t[]$  with a size of four times the input size  $n$ :
```cpp
int n, t[4*MAXN];
```

The procedure for constructing the Segment Tree from a given array  $a[]$  looks like this: it is a recursive function with the parameters  $a[]$  (the input array),  $v$  (the index of the current vertex), and the boundaries  $tl$  and  $tr$  of the current segment. In the main program this function will be called with the parameters of the root vertex:  $v = 1$ ,  $tl = 0$ , and  $tr = n - 1$ .

```cpp
void build(int a[], int v, int l, int r) {
    if (l == r) {
        t[v] = a[l];
    } else {
        int mid = (tl + tr) / 2;
        build(a, v*2, l, mid);
        build(a, v*2+1, mid+1, r);
        t[v] = t[v*2] + t[v*2+1];
    }
}

int sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}
```

