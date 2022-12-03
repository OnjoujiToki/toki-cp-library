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
  bundledCode: "#line 1 \"fenwick.cpp\"\ntemplate <typename T>\nstruct FenwickTree\
    \ {\n  std::vector<T> bit;\n  int n;\n  FenwickTree(int _n) : n(_n), bit(_n) {}\n\
    \  // 0 based\n  T sum(int r) {\n    int ret = 0;\n    for (; r >= 0; r = (r &\
    \ (r + 1)) - 1) ret += bit[r];\n    return ret;\n  }\n  // try commits:::\n  T\
    \ sum(int l, int r) { return sum(r) - sum(l - 1); }\n\n  void add(int idx, int\
    \ delta) {\n    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;\n  }\n\
    };\n"
  code: "template <typename T>\nstruct FenwickTree {\n  std::vector<T> bit;\n  int\
    \ n;\n  FenwickTree(int _n) : n(_n), bit(_n) {}\n  // 0 based\n  T sum(int r)\
    \ {\n    int ret = 0;\n    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];\n\
    \    return ret;\n  }\n  // try commits:::\n  T sum(int l, int r) { return sum(r)\
    \ - sum(l - 1); }\n\n  void add(int idx, int delta) {\n    for (; idx < n; idx\
    \ = idx | (idx + 1)) bit[idx] += delta;\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: fenwick.cpp
  requiredBy: []
  timestamp: '2022-12-02 22:21:20-08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: fenwick.cpp
layout: document
redirect_from:
- /library/fenwick.cpp
- /library/fenwick.cpp.html
title: fenwick.cpp
---
