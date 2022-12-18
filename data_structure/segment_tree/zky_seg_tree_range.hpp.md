---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/segment_tree/zky_seg_tree_range.hpp\"\n//\
    \ credit: emthrm.github.io/library\n#include <algorithm>\n#include <limits>\n\
    #include <vector>\n\ntemplate <typename T>\nstruct LazySegmentTree {\n  using\
    \ Monoid = typename T::Monoid;\n  using LazyMonoid = typename T::LazyMonoid;\n\
    \n  explicit LazySegmentTree(const int n)\n      : LazySegmentTree(std::vector<Monoid>(n,\
    \ T::m_id())) {}\n\n  explicit LazySegmentTree(const std::vector<Monoid>& a)\n\
    \      : n(a.size()), height(0) {\n    while ((1 << height) < n) ++height;\n \
    \   sz = 1 << height;\n    lazy.assign(sz, T::lazy_id());\n    data.assign(sz\
    \ << 1, T::m_id());\n    std::copy(a.begin(), a.end(), data.begin() + sz);\n \
    \   for (int i = sz - 1; i > 0; --i) {\n      data[i] = T::m_merge(data[i << 1],\
    \ data[(i << 1) + 1]);\n    }\n  }\n\n  void set(int idx, const Monoid val) {\n\
    \    idx += sz;\n    for (int i = height; i > 0; --i) {\n      propagate(idx >>\
    \ i);\n    }\n    data[idx] = val;\n    for (int i = 1; i <= height; ++i) {\n\
    \      const int current_idx = idx >> i;\n      data[current_idx] =\n        \
    \  T::m_merge(data[current_idx << 1], data[(current_idx << 1) + 1]);\n    }\n\
    \  }\n\n  void apply(int idx, const LazyMonoid val) {\n    idx += sz;\n    for\
    \ (int i = height; i > 0; --i) {\n      propagate(idx >> i);\n    }\n    data[idx]\
    \ = T::apply(data[idx], val);\n    for (int i = 1; i <= height; ++i) {\n     \
    \ const int current_idx = idx >> i;\n      data[current_idx] =\n          T::m_merge(data[current_idx\
    \ << 1], data[(current_idx << 1) + 1]);\n    }\n  }\n\n  void apply(int left,\
    \ int right, const LazyMonoid val) {\n    if (right <= left) return;\n    left\
    \ += sz;\n    right += sz;\n    const int ctz_left = __builtin_ctz(left);\n  \
    \  for (int i = height; i > ctz_left; --i) {\n      propagate(left >> i);\n  \
    \  }\n    const int ctz_right = __builtin_ctz(right);\n    for (int i = height;\
    \ i > ctz_right; --i) {\n      propagate(right >> i);\n    }\n    for (int l =\
    \ left, r = right; l < r; l >>= 1, r >>= 1) {\n      if (l & 1) apply_sub(l++,\
    \ val);\n      if (r & 1) apply_sub(--r, val);\n    }\n    for (int i = left >>\
    \ (ctz_left + 1); i > 0; i >>= 1) {\n      data[i] = T::m_merge(data[i << 1],\
    \ data[(i << 1) + 1]);\n    }\n    for (int i = right >> (ctz_right + 1); i >\
    \ 0; i >>= 1) {\n      data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);\n\
    \    }\n  }\n\n  Monoid get(int left, int right) {\n    if (right <= left) return\
    \ T::m_id();\n    left += sz;\n    right += sz;\n    const int ctz_left = __builtin_ctz(left);\n\
    \    for (int i = height; i > ctz_left; --i) {\n      propagate(left >> i);\n\
    \    }\n    const int ctz_right = __builtin_ctz(right);\n    for (int i = height;\
    \ i > ctz_right; --i) {\n      propagate(right >> i);\n    }\n    Monoid res_l\
    \ = T::m_id(), res_r = T::m_id();\n    for (; left < right; left >>= 1, right\
    \ >>= 1) {\n      if (left & 1) res_l = T::m_merge(res_l, data[left++]);\n   \
    \   if (right & 1) res_r = T::m_merge(data[--right], res_r);\n    }\n    return\
    \ T::m_merge(res_l, res_r);\n  }\n\n  Monoid operator[](const int idx) {\n   \
    \ const int node = idx + sz;\n    for (int i = height; i > 0; --i) {\n      propagate(node\
    \ >> i);\n    }\n    return data[node];\n  }\n\n  template <typename G>\n  int\
    \ find_right(int left, const G g) {\n    if (left >= n) return n;\n    left +=\
    \ sz;\n    for (int i = height; i > 0; --i) {\n      propagate(left >> i);\n \
    \   }\n    Monoid val = T::m_id();\n    do {\n      while (!(left & 1)) left >>=\
    \ 1;\n      Monoid nxt = T::m_merge(val, data[left]);\n      if (!g(nxt)) {\n\
    \        while (left < sz) {\n          propagate(left);\n          left <<= 1;\n\
    \          nxt = T::m_merge(val, data[left]);\n          if (g(nxt)) {\n     \
    \       val = nxt;\n            ++left;\n          }\n        }\n        return\
    \ left - sz;\n      }\n      val = nxt;\n      ++left;\n    } while (__builtin_popcount(left)\
    \ > 1);\n    return n;\n  }\n\n  template <typename G>\n  int find_left(int right,\
    \ const G g) {\n    if (right <= 0) return -1;\n    right += sz;\n    for (int\
    \ i = height; i > 0; --i) {\n      propagate((right - 1) >> i);\n    }\n    Monoid\
    \ val = T::m_id();\n    do {\n      --right;\n      while (right > 1 && (right\
    \ & 1)) right >>= 1;\n      Monoid nxt = T::m_merge(data[right], val);\n     \
    \ if (!g(nxt)) {\n        while (right < sz) {\n          propagate(right);\n\
    \          right = (right << 1) + 1;\n          nxt = T::m_merge(data[right],\
    \ val);\n          if (g(nxt)) {\n            val = nxt;\n            --right;\n\
    \          }\n        }\n        return right - sz;\n      }\n      val = nxt;\n\
    \    } while (__builtin_popcount(right) > 1);\n    return -1;\n  }\n\n  const\
    \ int n;\n  int sz, height;\n  std::vector<Monoid> data;\n  std::vector<LazyMonoid>\
    \ lazy;\n\n  void apply_sub(const int idx, const LazyMonoid& val) {\n    data[idx]\
    \ = T::apply(data[idx], val);\n    if (idx < sz) lazy[idx] = T::lazy_merge(lazy[idx],\
    \ val);\n  }\n\n  void propagate(const int idx) {\n    apply_sub(idx << 1, lazy[idx]);\n\
    \    apply_sub((idx << 1) + 1, lazy[idx]);\n    lazy[idx] = T::lazy_id();\n  }\n\
    };\n\nnamespace monoid {\n\ntemplate <typename T>\nstruct RangeMinimumAndUpdateQuery\
    \ {\n  using Monoid = T;\n  using LazyMonoid = T;\n  static constexpr Monoid m_id()\
    \ { return std::numeric_limits<Monoid>::max(); }\n  static constexpr LazyMonoid\
    \ lazy_id() {\n    return std::numeric_limits<LazyMonoid>::max();\n  }\n  static\
    \ Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n\
    \  }\n  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b)\
    \ {\n    return b == lazy_id() ? a : b;\n  }\n  static Monoid apply(const Monoid&\
    \ a, const LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n  }\n};\n\ntemplate\
    \ <typename T>\nstruct RangeMaximumAndUpdateQuery {\n  using Monoid = T;\n  using\
    \ LazyMonoid = T;\n  static constexpr Monoid m_id() {\n    return std::numeric_limits<Monoid>::lowest();\n\
    \  }\n  static constexpr LazyMonoid lazy_id() {\n    return std::numeric_limits<LazyMonoid>::lowest();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ std::max(a, b);\n  }\n  static LazyMonoid lazy_merge(const LazyMonoid& a, const\
    \ LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n  }\n  static Monoid apply(const\
    \ Monoid& a, const LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n  }\n\
    };\n\ntemplate <typename T, T Inf>\nstruct RangeMinimumAndAddQuery {\n  using\
    \ Monoid = T;\n  using LazyMonoid = T;\n  static constexpr Monoid m_id() { return\
    \ Inf; }\n  static constexpr LazyMonoid lazy_id() { return 0; }\n  static Monoid\
    \ m_merge(const Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n  }\n\
    \  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {\n\
    \    return a + b;\n  }\n  static Monoid apply(const Monoid& a, const LazyMonoid&\
    \ b) { return a + b; }\n};\n\ntemplate <typename T, T Inf>\nstruct RangeMaximumAndAddQuery\
    \ {\n  using Monoid = T;\n  using LazyMonoid = T;\n  static constexpr Monoid m_id()\
    \ { return -Inf; }\n  static constexpr LazyMonoid lazy_id() { return 0; }\n  static\
    \ Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::max(a, b);\n\
    \  }\n  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b)\
    \ {\n    return a + b;\n  }\n  static Monoid apply(const Monoid& a, const LazyMonoid&\
    \ b) { return a + b; }\n};\n\ntemplate <typename T>\nstruct RangeSumAndUpdateQuery\
    \ {\n  using Monoid = struct {\n    T sum;\n    int len;\n  };\n  using LazyMonoid\
    \ = T;\n  static std::vector<Monoid> init(const int n) {\n    return std::vector<Monoid>(n,\
    \ Monoid{0, 1});\n  }\n  static constexpr Monoid m_id() { return {0, 0}; }\n \
    \ static constexpr LazyMonoid lazy_id() {\n    return std::numeric_limits<LazyMonoid>::max();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ Monoid{a.sum + b.sum, a.len + b.len};\n  }\n  static LazyMonoid lazy_merge(const\
    \ LazyMonoid& a, const LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n\
    \  }\n  static Monoid apply(const Monoid& a, const LazyMonoid& b) {\n    return\
    \ Monoid{b == lazy_id() ? a.sum : b * a.len, a.len};\n  }\n};\n\ntemplate <typename\
    \ T>\nstruct RangeSumAndAddQuery {\n  using Monoid = struct {\n    T sum;\n  \
    \  int len;\n  };\n  using LazyMonoid = T;\n  static std::vector<Monoid> init(const\
    \ int n) {\n    return std::vector<Monoid>(n, Monoid{0, 1});\n  }\n  static constexpr\
    \ Monoid m_id() { return {0, 0}; }\n  static constexpr LazyMonoid lazy_id() {\
    \ return 0; }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n \
    \   return Monoid{a.sum + b.sum, a.len + b.len};\n  }\n  static LazyMonoid lazy_merge(const\
    \ LazyMonoid& a, const LazyMonoid& b) {\n    return a + b;\n  }\n  static Monoid\
    \ apply(const Monoid& a, const LazyMonoid& b) {\n    return Monoid{a.sum + b *\
    \ a.len, a.len};\n  }\n};\n\n}  // namespace monoid\n"
  code: "#pragma once\n// credit: emthrm.github.io/library\n#include <algorithm>\n\
    #include <limits>\n#include <vector>\n\ntemplate <typename T>\nstruct LazySegmentTree\
    \ {\n  using Monoid = typename T::Monoid;\n  using LazyMonoid = typename T::LazyMonoid;\n\
    \n  explicit LazySegmentTree(const int n)\n      : LazySegmentTree(std::vector<Monoid>(n,\
    \ T::m_id())) {}\n\n  explicit LazySegmentTree(const std::vector<Monoid>& a)\n\
    \      : n(a.size()), height(0) {\n    while ((1 << height) < n) ++height;\n \
    \   sz = 1 << height;\n    lazy.assign(sz, T::lazy_id());\n    data.assign(sz\
    \ << 1, T::m_id());\n    std::copy(a.begin(), a.end(), data.begin() + sz);\n \
    \   for (int i = sz - 1; i > 0; --i) {\n      data[i] = T::m_merge(data[i << 1],\
    \ data[(i << 1) + 1]);\n    }\n  }\n\n  void set(int idx, const Monoid val) {\n\
    \    idx += sz;\n    for (int i = height; i > 0; --i) {\n      propagate(idx >>\
    \ i);\n    }\n    data[idx] = val;\n    for (int i = 1; i <= height; ++i) {\n\
    \      const int current_idx = idx >> i;\n      data[current_idx] =\n        \
    \  T::m_merge(data[current_idx << 1], data[(current_idx << 1) + 1]);\n    }\n\
    \  }\n\n  void apply(int idx, const LazyMonoid val) {\n    idx += sz;\n    for\
    \ (int i = height; i > 0; --i) {\n      propagate(idx >> i);\n    }\n    data[idx]\
    \ = T::apply(data[idx], val);\n    for (int i = 1; i <= height; ++i) {\n     \
    \ const int current_idx = idx >> i;\n      data[current_idx] =\n          T::m_merge(data[current_idx\
    \ << 1], data[(current_idx << 1) + 1]);\n    }\n  }\n\n  void apply(int left,\
    \ int right, const LazyMonoid val) {\n    if (right <= left) return;\n    left\
    \ += sz;\n    right += sz;\n    const int ctz_left = __builtin_ctz(left);\n  \
    \  for (int i = height; i > ctz_left; --i) {\n      propagate(left >> i);\n  \
    \  }\n    const int ctz_right = __builtin_ctz(right);\n    for (int i = height;\
    \ i > ctz_right; --i) {\n      propagate(right >> i);\n    }\n    for (int l =\
    \ left, r = right; l < r; l >>= 1, r >>= 1) {\n      if (l & 1) apply_sub(l++,\
    \ val);\n      if (r & 1) apply_sub(--r, val);\n    }\n    for (int i = left >>\
    \ (ctz_left + 1); i > 0; i >>= 1) {\n      data[i] = T::m_merge(data[i << 1],\
    \ data[(i << 1) + 1]);\n    }\n    for (int i = right >> (ctz_right + 1); i >\
    \ 0; i >>= 1) {\n      data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);\n\
    \    }\n  }\n\n  Monoid get(int left, int right) {\n    if (right <= left) return\
    \ T::m_id();\n    left += sz;\n    right += sz;\n    const int ctz_left = __builtin_ctz(left);\n\
    \    for (int i = height; i > ctz_left; --i) {\n      propagate(left >> i);\n\
    \    }\n    const int ctz_right = __builtin_ctz(right);\n    for (int i = height;\
    \ i > ctz_right; --i) {\n      propagate(right >> i);\n    }\n    Monoid res_l\
    \ = T::m_id(), res_r = T::m_id();\n    for (; left < right; left >>= 1, right\
    \ >>= 1) {\n      if (left & 1) res_l = T::m_merge(res_l, data[left++]);\n   \
    \   if (right & 1) res_r = T::m_merge(data[--right], res_r);\n    }\n    return\
    \ T::m_merge(res_l, res_r);\n  }\n\n  Monoid operator[](const int idx) {\n   \
    \ const int node = idx + sz;\n    for (int i = height; i > 0; --i) {\n      propagate(node\
    \ >> i);\n    }\n    return data[node];\n  }\n\n  template <typename G>\n  int\
    \ find_right(int left, const G g) {\n    if (left >= n) return n;\n    left +=\
    \ sz;\n    for (int i = height; i > 0; --i) {\n      propagate(left >> i);\n \
    \   }\n    Monoid val = T::m_id();\n    do {\n      while (!(left & 1)) left >>=\
    \ 1;\n      Monoid nxt = T::m_merge(val, data[left]);\n      if (!g(nxt)) {\n\
    \        while (left < sz) {\n          propagate(left);\n          left <<= 1;\n\
    \          nxt = T::m_merge(val, data[left]);\n          if (g(nxt)) {\n     \
    \       val = nxt;\n            ++left;\n          }\n        }\n        return\
    \ left - sz;\n      }\n      val = nxt;\n      ++left;\n    } while (__builtin_popcount(left)\
    \ > 1);\n    return n;\n  }\n\n  template <typename G>\n  int find_left(int right,\
    \ const G g) {\n    if (right <= 0) return -1;\n    right += sz;\n    for (int\
    \ i = height; i > 0; --i) {\n      propagate((right - 1) >> i);\n    }\n    Monoid\
    \ val = T::m_id();\n    do {\n      --right;\n      while (right > 1 && (right\
    \ & 1)) right >>= 1;\n      Monoid nxt = T::m_merge(data[right], val);\n     \
    \ if (!g(nxt)) {\n        while (right < sz) {\n          propagate(right);\n\
    \          right = (right << 1) + 1;\n          nxt = T::m_merge(data[right],\
    \ val);\n          if (g(nxt)) {\n            val = nxt;\n            --right;\n\
    \          }\n        }\n        return right - sz;\n      }\n      val = nxt;\n\
    \    } while (__builtin_popcount(right) > 1);\n    return -1;\n  }\n\n  const\
    \ int n;\n  int sz, height;\n  std::vector<Monoid> data;\n  std::vector<LazyMonoid>\
    \ lazy;\n\n  void apply_sub(const int idx, const LazyMonoid& val) {\n    data[idx]\
    \ = T::apply(data[idx], val);\n    if (idx < sz) lazy[idx] = T::lazy_merge(lazy[idx],\
    \ val);\n  }\n\n  void propagate(const int idx) {\n    apply_sub(idx << 1, lazy[idx]);\n\
    \    apply_sub((idx << 1) + 1, lazy[idx]);\n    lazy[idx] = T::lazy_id();\n  }\n\
    };\n\nnamespace monoid {\n\ntemplate <typename T>\nstruct RangeMinimumAndUpdateQuery\
    \ {\n  using Monoid = T;\n  using LazyMonoid = T;\n  static constexpr Monoid m_id()\
    \ { return std::numeric_limits<Monoid>::max(); }\n  static constexpr LazyMonoid\
    \ lazy_id() {\n    return std::numeric_limits<LazyMonoid>::max();\n  }\n  static\
    \ Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n\
    \  }\n  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b)\
    \ {\n    return b == lazy_id() ? a : b;\n  }\n  static Monoid apply(const Monoid&\
    \ a, const LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n  }\n};\n\ntemplate\
    \ <typename T>\nstruct RangeMaximumAndUpdateQuery {\n  using Monoid = T;\n  using\
    \ LazyMonoid = T;\n  static constexpr Monoid m_id() {\n    return std::numeric_limits<Monoid>::lowest();\n\
    \  }\n  static constexpr LazyMonoid lazy_id() {\n    return std::numeric_limits<LazyMonoid>::lowest();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ std::max(a, b);\n  }\n  static LazyMonoid lazy_merge(const LazyMonoid& a, const\
    \ LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n  }\n  static Monoid apply(const\
    \ Monoid& a, const LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n  }\n\
    };\n\ntemplate <typename T, T Inf>\nstruct RangeMinimumAndAddQuery {\n  using\
    \ Monoid = T;\n  using LazyMonoid = T;\n  static constexpr Monoid m_id() { return\
    \ Inf; }\n  static constexpr LazyMonoid lazy_id() { return 0; }\n  static Monoid\
    \ m_merge(const Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n  }\n\
    \  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {\n\
    \    return a + b;\n  }\n  static Monoid apply(const Monoid& a, const LazyMonoid&\
    \ b) { return a + b; }\n};\n\ntemplate <typename T, T Inf>\nstruct RangeMaximumAndAddQuery\
    \ {\n  using Monoid = T;\n  using LazyMonoid = T;\n  static constexpr Monoid m_id()\
    \ { return -Inf; }\n  static constexpr LazyMonoid lazy_id() { return 0; }\n  static\
    \ Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::max(a, b);\n\
    \  }\n  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b)\
    \ {\n    return a + b;\n  }\n  static Monoid apply(const Monoid& a, const LazyMonoid&\
    \ b) { return a + b; }\n};\n\ntemplate <typename T>\nstruct RangeSumAndUpdateQuery\
    \ {\n  using Monoid = struct {\n    T sum;\n    int len;\n  };\n  using LazyMonoid\
    \ = T;\n  static std::vector<Monoid> init(const int n) {\n    return std::vector<Monoid>(n,\
    \ Monoid{0, 1});\n  }\n  static constexpr Monoid m_id() { return {0, 0}; }\n \
    \ static constexpr LazyMonoid lazy_id() {\n    return std::numeric_limits<LazyMonoid>::max();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ Monoid{a.sum + b.sum, a.len + b.len};\n  }\n  static LazyMonoid lazy_merge(const\
    \ LazyMonoid& a, const LazyMonoid& b) {\n    return b == lazy_id() ? a : b;\n\
    \  }\n  static Monoid apply(const Monoid& a, const LazyMonoid& b) {\n    return\
    \ Monoid{b == lazy_id() ? a.sum : b * a.len, a.len};\n  }\n};\n\ntemplate <typename\
    \ T>\nstruct RangeSumAndAddQuery {\n  using Monoid = struct {\n    T sum;\n  \
    \  int len;\n  };\n  using LazyMonoid = T;\n  static std::vector<Monoid> init(const\
    \ int n) {\n    return std::vector<Monoid>(n, Monoid{0, 1});\n  }\n  static constexpr\
    \ Monoid m_id() { return {0, 0}; }\n  static constexpr LazyMonoid lazy_id() {\
    \ return 0; }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n \
    \   return Monoid{a.sum + b.sum, a.len + b.len};\n  }\n  static LazyMonoid lazy_merge(const\
    \ LazyMonoid& a, const LazyMonoid& b) {\n    return a + b;\n  }\n  static Monoid\
    \ apply(const Monoid& a, const LazyMonoid& b) {\n    return Monoid{a.sum + b *\
    \ a.len, a.len};\n  }\n};\n\n}  // namespace monoid"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree/zky_seg_tree_range.hpp
  requiredBy: []
  timestamp: '2022-12-18 18:47:30-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segment_tree/zky_seg_tree_range.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/zky_seg_tree_range.hpp
- /library/data_structure/segment_tree/zky_seg_tree_range.hpp.html
title: data_structure/segment_tree/zky_seg_tree_range.hpp
---
