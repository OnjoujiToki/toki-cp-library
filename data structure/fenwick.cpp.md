---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data structure/fenwick.cpp\"\ntemplate <typename T>\nstruct\
    \ FenwickTree {\n  std::vector<T> bit;\n  int n;\n  FenwickTree(int _n) : n(_n),\
    \ bit(_n) {}\n  FenwickTree(std::vector<T> a) {\n    bit.resize(n, 0);\n    for\
    \ (int i = 0; i < (int)a.size(); i++) add(i, (int)a[i]);\n  }\n  T sum(int r)\
    \ {\n    int ret = 0;\n    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];\n\
    \    return ret;\n  }\n\n  T sum(int l, int r) { return sum(r) - sum(l - 1); }\
    \  // [l, r]\n\n  void add(int idx, int delta) {\n    for (; idx < n; idx = idx\
    \ | (idx + 1)) bit[idx] += delta;\n  }\n};\n"
  code: "template <typename T>\nstruct FenwickTree {\n  std::vector<T> bit;\n  int\
    \ n;\n  FenwickTree(int _n) : n(_n), bit(_n) {}\n  FenwickTree(std::vector<T>\
    \ a) {\n    bit.resize(n, 0);\n    for (int i = 0; i < (int)a.size(); i++) add(i,\
    \ (int)a[i]);\n  }\n  T sum(int r) {\n    int ret = 0;\n    for (; r >= 0; r =\
    \ (r & (r + 1)) - 1) ret += bit[r];\n    return ret;\n  }\n\n  T sum(int l, int\
    \ r) { return sum(r) - sum(l - 1); }  // [l, r]\n\n  void add(int idx, int delta)\
    \ {\n    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data structure/fenwick.cpp
  requiredBy: []
  timestamp: '2022-12-02 23:38:34-08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data structure/fenwick.cpp
layout: document
redirect_from:
- /library/data structure/fenwick.cpp
- /library/data structure/fenwick.cpp.html
title: data structure/fenwick.cpp
---
