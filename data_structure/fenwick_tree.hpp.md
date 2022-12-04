---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tests/data_structure/point_add_range_query.test.cpp
    title: tests/data_structure/point_add_range_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/fenwick_tree.hpp\"\ntemplate <typename T>\n\
    struct FenwickTree {\n  std::vector<T> bit;\n  int n;\n  FenwickTree(int _n) :\
    \ n(_n), bit(_n) {}\n\n  T sum(int r) {\n    int ret = 0;\n    for (; r >= 0;\
    \ r = (r & (r + 1)) - 1) ret += bit[r];\n    return ret;\n  }\n\n  T sum(int l,\
    \ int r) { return sum(r) - sum(l - 1); }  // [l, r]\n\n  void add(int idx, int\
    \ delta) {\n    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;\n  }\n\
    };\n"
  code: "template <typename T>\nstruct FenwickTree {\n  std::vector<T> bit;\n  int\
    \ n;\n  FenwickTree(int _n) : n(_n), bit(_n) {}\n\n  T sum(int r) {\n    int ret\
    \ = 0;\n    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];\n    return ret;\n\
    \  }\n\n  T sum(int l, int r) { return sum(r) - sum(l - 1); }  // [l, r]\n\n \
    \ void add(int idx, int delta) {\n    for (; idx < n; idx = idx | (idx + 1)) bit[idx]\
    \ += delta;\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/fenwick_tree.hpp
  requiredBy: []
  timestamp: '2022-12-03 00:59:54-08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tests/data_structure/point_add_range_query.test.cpp
documentation_of: data_structure/fenwick_tree.hpp
layout: document
title: Fenwick Tree
---

## Description

- `FenwickTree(_n)`: $O(N)$ 建立一个长度为 $n$ 的树状数组。
- `T sum(int r)`: $O(logN)$ 返回区间 $[0, r]$ 的和 。
- `T sum(int l, int r)`: $O(logN)$ 返回区间 $[l, r]$ 的和
- `void add(int idx, int delta)`: $O(logN)$ 单点给 `idx` 增加 `delta` 的值 ss