---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"tests/datastructure/pointAddRangeQuery.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cmath>\n#include <cstring>\n#include\
    \ <ctime>\n#include <deque>\n#include <iomanip>\n#include <iostream>\n#include\
    \ <map>\n#include <numeric>\n#include <queue>\n#include <set>\n#include <sstream>\n\
    #include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n#include\
    \ <vector>\n\ntemplate <typename T>\nstruct FenwickTree {\n  std::vector<T> bit;\n\
    \  int n;\n  FenwickTree(int _n) : n(_n), bit(_n) {}\n  FenwickTree(std::vector<T>\
    \ a) {\n    bit.resize(n, 0);\n    for (int i = 0; i < (int)a.size(); i++) add(i,\
    \ (int)a[i]);\n  }\n  T sum(int r) {\n    int ret = 0;\n    for (; r >= 0; r =\
    \ (r & (r + 1)) - 1) ret += bit[r];\n    return ret;\n  }\n\n  T sum(int l, int\
    \ r) { return sum(r) - sum(l - 1); }\n\n  void add(int idx, int delta) {\n   \
    \ for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;\n  }\n};\n\nvoid solve()\
    \ {\n  int N, Q;\n  std::cin >> N >> Q;\n  std::vector<int> a(N);\n  for (int&\
    \ x : a) std::cin >> x;\n  FenwickTree<int> tree(a);\n  while (Q--) {\n    int\
    \ op, a, b;\n    std::cin >> op >> a >> b;\n    if (op) {\n      std::cout <<\
    \ tree.sum(a, b - 1) << '\\n';\n    } else {\n      tree.add(a, b);\n    }\n \
    \ }\n}\nint main() {\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \n  solve();\n\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    #include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstring>\n#include <ctime>\n#include <deque>\n#include <iomanip>\n#include\
    \ <iostream>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <sstream>\n#include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n\
    #include <vector>\n\ntemplate <typename T>\nstruct FenwickTree {\n  std::vector<T>\
    \ bit;\n  int n;\n  FenwickTree(int _n) : n(_n), bit(_n) {}\n  FenwickTree(std::vector<T>\
    \ a) {\n    bit.resize(n, 0);\n    for (int i = 0; i < (int)a.size(); i++) add(i,\
    \ (int)a[i]);\n  }\n  T sum(int r) {\n    int ret = 0;\n    for (; r >= 0; r =\
    \ (r & (r + 1)) - 1) ret += bit[r];\n    return ret;\n  }\n\n  T sum(int l, int\
    \ r) { return sum(r) - sum(l - 1); }\n\n  void add(int idx, int delta) {\n   \
    \ for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;\n  }\n};\n\nvoid solve()\
    \ {\n  int N, Q;\n  std::cin >> N >> Q;\n  std::vector<int> a(N);\n  for (int&\
    \ x : a) std::cin >> x;\n  FenwickTree<int> tree(a);\n  while (Q--) {\n    int\
    \ op, a, b;\n    std::cin >> op >> a >> b;\n    if (op) {\n      std::cout <<\
    \ tree.sum(a, b - 1) << '\\n';\n    } else {\n      tree.add(a, b);\n    }\n \
    \ }\n}\nint main() {\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \n  solve();\n\n  return 0;\n}"
  dependsOn: []
  isVerificationFile: false
  path: tests/datastructure/pointAddRangeQuery.cpp
  requiredBy: []
  timestamp: '2022-12-02 23:38:34-08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tests/datastructure/pointAddRangeQuery.cpp
layout: document
redirect_from:
- /library/tests/datastructure/pointAddRangeQuery.cpp
- /library/tests/datastructure/pointAddRangeQuery.cpp.html
title: tests/datastructure/pointAddRangeQuery.cpp
---
