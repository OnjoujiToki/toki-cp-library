---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.11.1/x64/lib/python3.11/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.11.1/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.11.1/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.11.1/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../../data_structure/segment_tree/zkw_seg_tree.hpp:\
    \ line -1: no such header\n"
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
  dependsOn: []
  isVerificationFile: true
  path: tests/data_structure/point_add_range_min.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: tests/data_structure/point_add_range_min.test.cpp
layout: document
redirect_from:
- /verify/tests/data_structure/point_add_range_min.test.cpp
- /verify/tests/data_structure/point_add_range_min.test.cpp.html
title: tests/data_structure/point_add_range_min.test.cpp
---
