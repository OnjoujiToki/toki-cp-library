---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: tests/data_structure/point_add_range_min.test.cpp
    title: tests/data_structure/point_add_range_min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/segment_tree/zkw_seg_tree.hpp\"\n#include\
    \ <algorithm>\n#include <limits>\n#include <vector>\n\ntemplate <typename T>\n\
    struct SegmentTree {\n  using Monoid = typename T::Monoid;\n\n  explicit SegmentTree(int\
    \ n) : SegmentTree(std::vector<Monoid>(n, T::id())) {}\n\n  explicit SegmentTree(const\
    \ std::vector<Monoid>& a) : n(a.size()), sz(1) {\n    while (sz < n) sz <<= 1;\n\
    \    data.assign(sz << 1, T::id());\n    std::copy(a.begin(), a.end(), data.begin()\
    \ + sz);\n    for (int i = sz - 1; i > 0; --i) {\n      data[i] = T::merge(data[i\
    \ << 1], data[(i << 1) + 1]);\n    }\n  }\n\n  void set(int idx, const Monoid\
    \ val) {\n    idx += sz;\n    data[idx] = val;\n    while (idx >>= 1)\n      data[idx]\
    \ = T::merge(data[idx << 1], data[(idx << 1) + 1]);\n  }\n\n  Monoid get(int left,\
    \ int right) const {\n    Monoid res_l = T::id(), res_r = T::id();\n    for (left\
    \ += sz, right += sz; left < right; left >>= 1, right >>= 1) {\n      if (left\
    \ & 1) res_l = T::merge(res_l, data[left++]);\n      if (right & 1) res_r = T::merge(data[--right],\
    \ res_r);\n    }\n    return T::merge(res_l, res_r);\n  }\n\n  Monoid operator[](const\
    \ int idx) const { return data[idx + sz]; }\n\n private:\n  const int n;\n  int\
    \ sz;  // sz + \u539F\u6570\u7EC4\u5750\u6807 = \u7EBF\u6BB5\u6811\u91CC\u7684\
    \u7F16\u53F7\uFF0C1 based\n  std::vector<Monoid> data;\n};\n\nnamespace monoid\
    \ {\n\ntemplate <typename T>\nstruct RangeMinimumQuery {\n  using Monoid = T;\n\
    \  static constexpr Monoid id() { return std::numeric_limits<Monoid>::max(); }\n\
    \  static Monoid merge(const Monoid& a, const Monoid& b) {\n    return std::min(a,\
    \ b);\n  }\n};\n\ntemplate <typename T>\nstruct RangeMaximumQuery {\n  using Monoid\
    \ = T;\n  static constexpr Monoid id() { return std::numeric_limits<Monoid>::lowest();\
    \ }\n  static Monoid merge(const Monoid& a, const Monoid& b) {\n    return std::max(a,\
    \ b);\n  }\n};\n\ntemplate <typename T>\nstruct RangeSumQuery {\n  using Monoid\
    \ = T;\n  static constexpr Monoid id() { return 0; }\n  static Monoid merge(const\
    \ Monoid& a, const Monoid& b) { return a + b; }\n};\n\n}  // namespace monoid\n"
  code: "#pragma once\n#include <algorithm>\n#include <limits>\n#include <vector>\n\
    \ntemplate <typename T>\nstruct SegmentTree {\n  using Monoid = typename T::Monoid;\n\
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
    \ const Monoid& b) { return a + b; }\n};\n\n}  // namespace monoid"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree/zkw_seg_tree.hpp
  requiredBy: []
  timestamp: '2022-12-05 18:04:03-08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tests/data_structure/point_add_range_min.test.cpp
documentation_of: data_structure/segment_tree/zkw_seg_tree.hpp
layout: document
title: ZKW Segment Tree
---

## Description

xie wan erfen zai gao..