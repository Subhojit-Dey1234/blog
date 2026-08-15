# Dynamic Programming and Bit Masking

First thing to make sure before using `bitmasks` for solving a problem is that it must be having small constraints as solution use `bitmasking` generally take up exponential time and memory.

`Bitmaskis` nothing but a binary number that represents something.

Consider the set A = {1, 2, 3, 4, 5}. We can represent any subset of A using bitmask of length 5 with an assumption that if `i-th` bit is set then it means `i-th` element is present in the subset.
If bit ii i is **set** (equal to 1), it means element element **is present** in the subset. If bit i is **0**, element​ is **absent**.

So bitmask `01010` represents `{2, 4}`

---
#### Common patterns

- **Check if bit `i` is set:** `(mask & (1 << i)) != 0`
- **Set bit `i`:** `mask |= (1 << i)`
- **Clear bit `i`:** `mask &= ~(1 << i)`
- **Toggle bit `i`:** `mask ^= (1 << i)`
- **Check if a mask is a subset of another:** `(a & b) == a`

Let say b = 01010

Set the `i-th` bit: `b | ( 1 << i )`  Let `i = 0` so
```
(1 << i ) = 000001
01010 | 00001 = 01011

The position at the end that is zero is 1
```

So now the subset includes the  0th element also, so the subset is `{ 1, 2, 4}`

Unset the `i-th bit` : `b & !(1 << i)`  Let `i = 1`

```
(1 << i)  = 00010
!(1 << i) = 11101
b & !(1 << i) = 01000
```

Check if the i-th bit is set,  i = 3

```
(1 << i) = 01000
01010&01000 = 01000
```

---
### Why and When to use Bitmask DP

The most significant limiting factor is N, the number of items being tracked by the mask. This is applied for a small set of operation mostly N=25

