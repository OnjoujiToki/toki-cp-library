---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/fenwick_tree.hpp
    title: data_structure/fenwick_tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
  bundledCode: "#line 1 \"tests/data_structure/point_add_range_query.test.cpp\"\n\
    #define PROBLEM \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstring>\n#include <ctime>\n#include <deque>\n#include <iomanip>\n#include\
    \ <iostream>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <sstream>\n#include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n\
    #include <vector>\n\n#line 1 \"data_structure/fenwick_tree.hpp\"\ntemplate <typename\
    \ T>\nstruct FenwickTree {\n  std::vector<T> bit;\n  int n;\n  FenwickTree(int\
    \ _n) : n(_n), bit(_n) {}\n  FenwickTree(std::vector<T> a) {\n    bit.resize(n,\
    \ 0);\n    for (int i = 0; i < (int)a.size(); i++) add(i, (int)a[i]);\n  }\n \
    \ T sum(int r) {\n    int ret = 0;\n    for (; r >= 0; r = (r & (r + 1)) - 1)\
    \ ret += bit[r];\n    return ret;\n  }\n\n  T sum(int l, int r) { return sum(r)\
    \ - sum(l - 1); }  // [l, r]\n\n  void add(int idx, int delta) {\n    for (; idx\
    \ < n; idx = idx | (idx + 1)) bit[idx] += delta;\n  }\n};\n#line 23 \"tests/data_structure/point_add_range_query.test.cpp\"\
    \n\nvoid solve() {\n  int N, Q;\n  std::cin >> N >> Q;\n  FenwickTree<long long>\
    \ tree(N);\n  while (Q--) {\n    int op, a, b;\n    std::cin >> op >> a >> b;\n\
    \n    if (op) {\n      std::cout << tree.sum(a - 1, b - 1) << '\\n';\n    } else\
    \ {\n      tree.add(a - 1, b);\n    }\n  }\n}\n\nint main() {\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n\n  solve();\n\n  return 0;\n}\n"
  code: "#define PROBLEM \\\n  \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstring>\n#include <ctime>\n#include <deque>\n#include <iomanip>\n#include\
    \ <iostream>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <sstream>\n#include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n\
    #include <vector>\n\n#include \"../../data_structure/fenwick_tree.hpp\"\n\nvoid\
    \ solve() {\n  int N, Q;\n  std::cin >> N >> Q;\n  FenwickTree<long long> tree(N);\n\
    \  while (Q--) {\n    int op, a, b;\n    std::cin >> op >> a >> b;\n\n    if (op)\
    \ {\n      std::cout << tree.sum(a - 1, b - 1) << '\\n';\n    } else {\n     \
    \ tree.add(a - 1, b);\n    }\n  }\n}\n\nint main() {\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n\n  solve();\n\n  return 0;\n}"
  dependsOn:
  - data_structure/fenwick_tree.hpp
  isVerificationFile: true
  path: tests/data_structure/point_add_range_query.test.cpp
  requiredBy: []
  timestamp: '2022-12-03 00:14:24-08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tests/data_structure/point_add_range_query.test.cpp
layout: document
redirect_from:
- /verify/tests/data_structure/point_add_range_query.test.cpp
- /verify/tests/data_structure/point_add_range_query.test.cpp.html
title: tests/data_structure/point_add_range_query.test.cpp
---
