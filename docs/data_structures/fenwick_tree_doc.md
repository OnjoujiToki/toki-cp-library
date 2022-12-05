---
title: Fenwick Tree
documentation_of: ../../data_structure/fenwick_tree.hpp
---

## Description

- `FenwickTree(_n)`: $O(N)$ 建立一个长度为 $n$ 的树状数组。
- `T sum(int r)`: $O(logN)$ 返回区间 $[0, r]$ 的和 。
- `T sum(int l, int r)`: $O(logN)$ 返回区间 $[l, r]$ 的和
- `void add(int idx, int delta)`: $O(logN)$ 单点给 `idx` 增加 `delta` 的值 