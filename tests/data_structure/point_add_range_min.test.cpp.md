---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segment_tree/zkw_seg_tree.hpp
    title: ZKW Segment Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
  bundledCode: "#line 2 \"tests/data_structure/point_add_range_min.test.cpp\"\n#define\
    \ PROBLEM \\\n  \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstring>\n#include <ctime>\n#include <deque>\n#include <iomanip>\n#include\
    \ <iostream>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <sstream>\n#include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n\
    #include <vector>\n\n#line 3 \"data_structure/segment_tree/zkw_seg_tree.hpp\"\n\
    #include <limits>\n#line 5 \"data_structure/segment_tree/zkw_seg_tree.hpp\"\n\n\
    template <typename T>\nstruct SegmentTree {\n  using Monoid = typename T::Monoid;\n\
    \n  explicit SegmentTree(int n) : SegmentTree(std::vector<Monoid>(n, T::id()))\
    \ {}\n\n  explicit SegmentTree(const std::vector<Monoid>& a) : n(a.size()), sz(1)\
    \ {\n    while (sz < n) sz <<= 1;\n    data.assign(sz << 1, T::id());\n    std::copy(a.begin(),\
    \ a.end(), data.begin() + sz);\n    for (int i = sz - 1; i > 0; --i) {\n     \
    \ data[i] = T::merge(data[i << 1], data[(i << 1) + 1]);\n    }\n  }\n\n  void\
    \ set(int idx, const Monoid val) {\n    idx += sz;\n    data[idx] = val;\n   \
    \ while (idx >>= 1)\n      data[idx] = T::merge(data[idx << 1], data[(idx << 1)\
    \ + 1]);\n  }\n\n  Monoid get(int left, int right) const {\n    Monoid res_l =\
    \ T::id(), res_r = T::id();\n    for (left += sz, right += sz; left < right; left\
    \ >>= 1, right >>= 1) {\n      if (left & 1) res_l = T::merge(res_l, data[left++]);\n\
    \      if (right & 1) res_r = T::merge(data[--right], res_r);\n    }\n    return\
    \ T::merge(res_l, res_r);\n  }\n\n  Monoid operator[](const int idx) const { return\
    \ data[idx + sz]; }\n\n private:\n  const int n;\n  int sz;  // sz + \u539F\u6570\
    \u7EC4\u5750\u6807 = \u7EBF\u6BB5\u6811\u91CC\u7684\u7F16\u53F7\uFF0C1 based\n\
    \  std::vector<Monoid> data;\n};\n\nnamespace monoid {\n\ntemplate <typename T>\n\
    struct RangeMinimumQuery {\n  using Monoid = T;\n  static constexpr Monoid id()\
    \ { return std::numeric_limits<Monoid>::max(); }\n  static Monoid merge(const\
    \ Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n  }\n};\n\ntemplate\
    \ <typename T>\nstruct RangeMaximumQuery {\n  using Monoid = T;\n  static constexpr\
    \ Monoid id() { return std::numeric_limits<Monoid>::lowest(); }\n  static Monoid\
    \ merge(const Monoid& a, const Monoid& b) {\n    return std::max(a, b);\n  }\n\
    };\n\ntemplate <typename T>\nstruct RangeSumQuery {\n  using Monoid = T;\n  static\
    \ constexpr Monoid id() { return 0; }\n  static Monoid merge(const Monoid& a,\
    \ const Monoid& b) { return a + b; }\n};\n\n}  // namespace monoid\n#line 24 \"\
    tests/data_structure/point_add_range_min.test.cpp\"\n\nvoid solve() {\n  int n;\n\
    \  std::cin >> n;\n  int q;\n  std::cin >> q;\n  std::vector<int> a(n, std::numeric_limits<int>::max());\n\
    \n  SegmentTree<monoid::RangeMinimumQuery<int>> st(a);\n  while (q--) {\n    int\
    \ op;\n    std::cin >> op;\n    if (!op) {\n      int idx, val;\n      std::cin\
    \ >> idx >> val;\n      st.set(idx, val);\n\n    } else {\n      int l, r;\n \
    \     std::cin >> l >> r;\n      std::cout << st.get(l, r + 1) << '\\n';\n   \
    \ }\n  }\n}\n\nint main() {\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \n  solve();\n\n  return 0;\n}\n"
  code: "#pragma once\n#define PROBLEM \\\n  \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
    \n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cmath>\n\
    #include <cstring>\n#include <ctime>\n#include <deque>\n#include <iomanip>\n#include\
    \ <iostream>\n#include <map>\n#include <numeric>\n#include <queue>\n#include <set>\n\
    #include <sstream>\n#include <tuple>\n#include <unordered_map>\n#include <unordered_set>\n\
    #include <vector>\n\n#include \"../../data_structure//segment_tree/zkw_seg_tree.hpp\"\
    \n\nvoid solve() {\n  int n;\n  std::cin >> n;\n  int q;\n  std::cin >> q;\n \
    \ std::vector<int> a(n, std::numeric_limits<int>::max());\n\n  SegmentTree<monoid::RangeMinimumQuery<int>>\
    \ st(a);\n  while (q--) {\n    int op;\n    std::cin >> op;\n    if (!op) {\n\
    \      int idx, val;\n      std::cin >> idx >> val;\n      st.set(idx, val);\n\
    \n    } else {\n      int l, r;\n      std::cin >> l >> r;\n      std::cout <<\
    \ st.get(l, r + 1) << '\\n';\n    }\n  }\n}\n\nint main() {\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n\n  solve();\n\n  return 0;\n}"
  dependsOn:
  - data_structure/segment_tree/zkw_seg_tree.hpp
  isVerificationFile: true
  path: tests/data_structure/point_add_range_min.test.cpp
  requiredBy: []
  timestamp: '2022-12-05 18:04:03-08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tests/data_structure/point_add_range_min.test.cpp
layout: document
redirect_from:
- /verify/tests/data_structure/point_add_range_min.test.cpp
- /verify/tests/data_structure/point_add_range_min.test.cpp.html
title: tests/data_structure/point_add_range_min.test.cpp
---
