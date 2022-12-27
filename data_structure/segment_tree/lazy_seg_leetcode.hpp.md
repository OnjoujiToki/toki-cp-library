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
  bundledCode: "#line 1 \"data_structure/segment_tree/lazy_seg_leetcode.hpp\"\ntemplate\
    \ <typename T>\nstruct LazySegmentTree {\n  using Monoid = typename T::Monoid;\n\
    \  using OperatorMonoid = typename T::OperatorMonoid;\n  explicit LazySegmentTree()\
    \ : LazySegmentTree(std::vector<Monoid>(1, T::m_id())){} \n  explicit LazySegmentTree(const\
    \ int n)\n      : LazySegmentTree(std::vector<Monoid>(n, T::m_id())) {}\n\n  explicit\
    \ LazySegmentTree(const std::vector<Monoid>& a)\n      : n(a.size()), height(0)\
    \ {\n    while ((1 << height) < n) ++height;\n    p2 = 1 << height;\n    lazy.assign(p2,\
    \ T::o_id());\n    data.assign(p2 << 1, T::m_id());\n    std::copy(a.begin(),\
    \ a.end(), data.begin() + p2);\n    for (int i = p2 - 1; i > 0; --i) {\n     \
    \ data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);\n    }\n  }\n\n  void\
    \ set(int idx, const Monoid val) {\n    idx += p2;\n    for (int i = height; i\
    \ > 0; --i) {\n      propagate(idx >> i);\n    }\n    data[idx] = val;\n    for\
    \ (int i = 1; i <= height; ++i) {\n      const int current_idx = idx >> i;\n \
    \     data[current_idx] =\n          T::m_merge(data[current_idx << 1], data[(current_idx\
    \ << 1) + 1]);\n    }\n  }\n\n  void apply(int idx, const OperatorMonoid val)\
    \ {\n    idx += p2;\n    for (int i = height; i > 0; --i) {\n      propagate(idx\
    \ >> i);\n    }\n    data[idx] = T::apply(data[idx], val);\n    for (int i = 1;\
    \ i <= height; ++i) {\n      const int current_idx = idx >> i;\n      data[current_idx]\
    \ =\n          T::m_merge(data[current_idx << 1], data[(current_idx << 1) + 1]);\n\
    \    }\n  }\n\n  void apply(int left, int right, const OperatorMonoid val) {\n\
    \    if (right <= left) return;\n    left += p2;\n    right += p2;\n    const\
    \ int ctz_left = __builtin_ctz(left);\n    for (int i = height; i > ctz_left;\
    \ --i) {\n      propagate(left >> i);\n    }\n    const int ctz_right = __builtin_ctz(right);\n\
    \    for (int i = height; i > ctz_right; --i) {\n      propagate(right >> i);\n\
    \    }\n    for (int l = left, r = right; l < r; l >>= 1, r >>= 1) {\n      if\
    \ (l & 1) apply_sub(l++, val);\n      if (r & 1) apply_sub(--r, val);\n    }\n\
    \    for (int i = left >> (ctz_left + 1); i > 0; i >>= 1) {\n      data[i] = T::m_merge(data[i\
    \ << 1], data[(i << 1) + 1]);\n    }\n    for (int i = right >> (ctz_right + 1);\
    \ i > 0; i >>= 1) {\n      data[i] = T::m_merge(data[i << 1], data[(i << 1) +\
    \ 1]);\n    }\n  }\n\n  Monoid get(int left, int right) {\n    if (right <= left)\
    \ return T::m_id();\n    left += p2;\n    right += p2;\n    const int ctz_left\
    \ = __builtin_ctz(left);\n    for (int i = height; i > ctz_left; --i) {\n    \
    \  propagate(left >> i);\n    }\n    const int ctz_right = __builtin_ctz(right);\n\
    \    for (int i = height; i > ctz_right; --i) {\n      propagate(right >> i);\n\
    \    }\n    Monoid res_l = T::m_id(), res_r = T::m_id();\n    for (; left < right;\
    \ left >>= 1, right >>= 1) {\n      if (left & 1) res_l = T::m_merge(res_l, data[left++]);\n\
    \      if (right & 1) res_r = T::m_merge(data[--right], res_r);\n    }\n    return\
    \ T::m_merge(res_l, res_r);\n  }\n\n  Monoid operator[](const int idx) {\n   \
    \ const int node = idx + p2;\n    for (int i = height; i > 0; --i) {\n      propagate(node\
    \ >> i);\n    }\n    return data[node];\n  }\n\n  template <typename G>\n  int\
    \ find_right(int left, const G g) {\n    if (left >= n) return n;\n    left +=\
    \ p2;\n    for (int i = height; i > 0; --i) {\n      propagate(left >> i);\n \
    \   }\n    Monoid val = T::m_id();\n    do {\n      while (!(left & 1)) left >>=\
    \ 1;\n      Monoid nxt = T::m_merge(val, data[left]);\n      if (!g(nxt)) {\n\
    \        while (left < p2) {\n          propagate(left);\n          left <<= 1;\n\
    \          nxt = T::m_merge(val, data[left]);\n          if (g(nxt)) {\n     \
    \       val = nxt;\n            ++left;\n          }\n        }\n        return\
    \ left - p2;\n      }\n      val = nxt;\n      ++left;\n    } while (__builtin_popcount(left)\
    \ > 1);\n    return n;\n  }\n\n  template <typename G>\n  int find_left(int right,\
    \ const G g) {\n    if (right <= 0) return -1;\n    right += p2;\n    for (int\
    \ i = height; i > 0; --i) {\n      propagate((right - 1) >> i);\n    }\n    Monoid\
    \ val = T::m_id();\n    do {\n      --right;\n      while (right > 1 && (right\
    \ & 1)) right >>= 1;\n      Monoid nxt = T::m_merge(data[right], val);\n     \
    \ if (!g(nxt)) {\n        while (right < p2) {\n          propagate(right);\n\
    \          right = (right << 1) + 1;\n          nxt = T::m_merge(data[right],\
    \ val);\n          if (g(nxt)) {\n            val = nxt;\n            --right;\n\
    \          }\n        }\n        return right - p2;\n      }\n      val = nxt;\n\
    \    } while (__builtin_popcount(right) > 1);\n    return -1;\n  }\n\n private:\n\
    \  int n;\n  int p2, height;\n  std::vector<Monoid> data;\n  std::vector<OperatorMonoid>\
    \ lazy;\n  LazySegmentTree(const LazySegmentTree &obj) : n(obj.n), p2(obj.p2),\
    \ height(obj.height), lazy(obj.lazy) {}\n\n  void apply_sub(const int idx, const\
    \ OperatorMonoid& val) {\n    data[idx] = T::apply(data[idx], val);\n    if (idx\
    \ < p2) lazy[idx] = T::o_merge(lazy[idx], val);\n  }\n\n  void propagate(const\
    \ int idx) {\n    // assert(1 <= idx && idx < p2);\n    apply_sub(idx << 1, lazy[idx]);\n\
    \    apply_sub((idx << 1) + 1, lazy[idx]);\n    lazy[idx] = T::o_id();\n  }\n\
    };\n\nnamespace monoid {\n\ntemplate <typename T>\nstruct RangeMinimumAndUpdateQuery\
    \ {\n  using Monoid = T;\n  using OperatorMonoid = T;\n  static constexpr Monoid\
    \ m_id() { return std::numeric_limits<Monoid>::max(); }\n  static constexpr OperatorMonoid\
    \ o_id() {\n    return std::numeric_limits<OperatorMonoid>::max();\n  }\n  static\
    \ Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n\
    \  }\n  static OperatorMonoid o_merge(const OperatorMonoid& a,\n             \
    \                   const OperatorMonoid& b) {\n    return b == o_id() ? a : b;\n\
    \  }\n  static Monoid apply(const Monoid& a, const OperatorMonoid& b) {\n    return\
    \ b == o_id() ? a : b;\n  }\n};\n\ntemplate <typename T>\nstruct RangeMaximumAndUpdateQuery\
    \ {\n  using Monoid = T;\n  using OperatorMonoid = T;\n  static constexpr Monoid\
    \ m_id() {\n    return std::numeric_limits<Monoid>::lowest();\n  }\n  static constexpr\
    \ OperatorMonoid o_id() {\n    return std::numeric_limits<OperatorMonoid>::lowest();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ std::max(a, b);\n  }\n  static OperatorMonoid o_merge(const OperatorMonoid&\
    \ a,\n                                const OperatorMonoid& b) {\n    return b\
    \ == o_id() ? a : b;\n  }\n  static Monoid apply(const Monoid& a, const OperatorMonoid&\
    \ b) {\n    return b == o_id()? a : b;\n  }\n};\n\ntemplate <typename T, T Inf>\n\
    struct RangeMinimumAndAddQuery {\n  using Monoid = T;\n  using OperatorMonoid\
    \ = T;\n  static constexpr Monoid m_id() { return Inf; }\n  static constexpr OperatorMonoid\
    \ o_id() { return 0; }\n  static Monoid m_merge(const Monoid& a, const Monoid&\
    \ b) {\n    return std::min(a, b);\n  }\n  static OperatorMonoid o_merge(const\
    \ OperatorMonoid& a,\n                                const OperatorMonoid& b)\
    \ {\n    return a + b;\n  }\n  static Monoid apply(const Monoid& a, const OperatorMonoid&\
    \ b) {\n    return a + b;\n  }\n};\n\ntemplate <typename T, T Inf>\nstruct RangeMaximumAndAddQuery\
    \ {\n  using Monoid = T;\n  using OperatorMonoid = T;\n  static constexpr Monoid\
    \ m_id() { return -Inf; }\n  static constexpr OperatorMonoid o_id() { return 0;\
    \ }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::max(a,\
    \ b);\n  }\n  static OperatorMonoid o_merge(const OperatorMonoid& a,\n       \
    \                         const OperatorMonoid& b) {\n    return a + b;\n  }\n\
    \  static Monoid apply(const Monoid& a, const OperatorMonoid& b) {\n    return\
    \ a + b;\n  }\n};\n\ntemplate <typename T>\nstruct RangeSumAndUpdateQuery {\n\
    \  using Monoid = struct { T sum; int len; };\n  using OperatorMonoid = T;\n \
    \ static std::vector<Monoid> init(const int n) {\n    return std::vector<Monoid>(n,\
    \ Monoid{0, 1});\n  }\n  static constexpr Monoid m_id() { return {0, 0}; }\n \
    \ static constexpr OperatorMonoid o_id() {\n    return std::numeric_limits<OperatorMonoid>::max();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ Monoid{a.sum + b.sum, a.len + b.len};\n  }\n  static OperatorMonoid o_merge(const\
    \ OperatorMonoid& a,\n                                const OperatorMonoid& b)\
    \ {\n    return b == o_id() ? a : b;\n  }\n  static Monoid apply(const Monoid&\
    \ a, const OperatorMonoid& b) {\n    return Monoid{b == o_id() ? a.sum : b * a.len,\
    \ a.len};\n  }\n};\n\ntemplate <typename T>\nstruct RangeSumAndAddQuery {\n  using\
    \ Monoid = struct { T sum; int len; };\n  using OperatorMonoid = T;\n  static\
    \ std::vector<Monoid> init(const int n) {\n    return std::vector<Monoid>(n, Monoid{0,\
    \ 1});\n  }\n  static constexpr Monoid m_id() { return {0, 0}; }\n  static constexpr\
    \ OperatorMonoid o_id() { return 0; }\n  static Monoid m_merge(const Monoid& a,\
    \ const Monoid& b) {\n    return Monoid{a.sum + b.sum, a.len + b.len};\n  }\n\
    \  static OperatorMonoid o_merge(const OperatorMonoid& a,\n                  \
    \              const OperatorMonoid& b) {\n    return a + b;\n  }\n  static Monoid\
    \ apply(const Monoid& a, const OperatorMonoid& b) {\n    return Monoid{a.sum +\
    \ b * a.len, a.len};\n  }\n};\n\n}  // namespace monoid\n"
  code: "template <typename T>\nstruct LazySegmentTree {\n  using Monoid = typename\
    \ T::Monoid;\n  using OperatorMonoid = typename T::OperatorMonoid;\n  explicit\
    \ LazySegmentTree() : LazySegmentTree(std::vector<Monoid>(1, T::m_id())){} \n\
    \  explicit LazySegmentTree(const int n)\n      : LazySegmentTree(std::vector<Monoid>(n,\
    \ T::m_id())) {}\n\n  explicit LazySegmentTree(const std::vector<Monoid>& a)\n\
    \      : n(a.size()), height(0) {\n    while ((1 << height) < n) ++height;\n \
    \   p2 = 1 << height;\n    lazy.assign(p2, T::o_id());\n    data.assign(p2 <<\
    \ 1, T::m_id());\n    std::copy(a.begin(), a.end(), data.begin() + p2);\n    for\
    \ (int i = p2 - 1; i > 0; --i) {\n      data[i] = T::m_merge(data[i << 1], data[(i\
    \ << 1) + 1]);\n    }\n  }\n\n  void set(int idx, const Monoid val) {\n    idx\
    \ += p2;\n    for (int i = height; i > 0; --i) {\n      propagate(idx >> i);\n\
    \    }\n    data[idx] = val;\n    for (int i = 1; i <= height; ++i) {\n      const\
    \ int current_idx = idx >> i;\n      data[current_idx] =\n          T::m_merge(data[current_idx\
    \ << 1], data[(current_idx << 1) + 1]);\n    }\n  }\n\n  void apply(int idx, const\
    \ OperatorMonoid val) {\n    idx += p2;\n    for (int i = height; i > 0; --i)\
    \ {\n      propagate(idx >> i);\n    }\n    data[idx] = T::apply(data[idx], val);\n\
    \    for (int i = 1; i <= height; ++i) {\n      const int current_idx = idx >>\
    \ i;\n      data[current_idx] =\n          T::m_merge(data[current_idx << 1],\
    \ data[(current_idx << 1) + 1]);\n    }\n  }\n\n  void apply(int left, int right,\
    \ const OperatorMonoid val) {\n    if (right <= left) return;\n    left += p2;\n\
    \    right += p2;\n    const int ctz_left = __builtin_ctz(left);\n    for (int\
    \ i = height; i > ctz_left; --i) {\n      propagate(left >> i);\n    }\n    const\
    \ int ctz_right = __builtin_ctz(right);\n    for (int i = height; i > ctz_right;\
    \ --i) {\n      propagate(right >> i);\n    }\n    for (int l = left, r = right;\
    \ l < r; l >>= 1, r >>= 1) {\n      if (l & 1) apply_sub(l++, val);\n      if\
    \ (r & 1) apply_sub(--r, val);\n    }\n    for (int i = left >> (ctz_left + 1);\
    \ i > 0; i >>= 1) {\n      data[i] = T::m_merge(data[i << 1], data[(i << 1) +\
    \ 1]);\n    }\n    for (int i = right >> (ctz_right + 1); i > 0; i >>= 1) {\n\
    \      data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);\n    }\n  }\n\n\
    \  Monoid get(int left, int right) {\n    if (right <= left) return T::m_id();\n\
    \    left += p2;\n    right += p2;\n    const int ctz_left = __builtin_ctz(left);\n\
    \    for (int i = height; i > ctz_left; --i) {\n      propagate(left >> i);\n\
    \    }\n    const int ctz_right = __builtin_ctz(right);\n    for (int i = height;\
    \ i > ctz_right; --i) {\n      propagate(right >> i);\n    }\n    Monoid res_l\
    \ = T::m_id(), res_r = T::m_id();\n    for (; left < right; left >>= 1, right\
    \ >>= 1) {\n      if (left & 1) res_l = T::m_merge(res_l, data[left++]);\n   \
    \   if (right & 1) res_r = T::m_merge(data[--right], res_r);\n    }\n    return\
    \ T::m_merge(res_l, res_r);\n  }\n\n  Monoid operator[](const int idx) {\n   \
    \ const int node = idx + p2;\n    for (int i = height; i > 0; --i) {\n      propagate(node\
    \ >> i);\n    }\n    return data[node];\n  }\n\n  template <typename G>\n  int\
    \ find_right(int left, const G g) {\n    if (left >= n) return n;\n    left +=\
    \ p2;\n    for (int i = height; i > 0; --i) {\n      propagate(left >> i);\n \
    \   }\n    Monoid val = T::m_id();\n    do {\n      while (!(left & 1)) left >>=\
    \ 1;\n      Monoid nxt = T::m_merge(val, data[left]);\n      if (!g(nxt)) {\n\
    \        while (left < p2) {\n          propagate(left);\n          left <<= 1;\n\
    \          nxt = T::m_merge(val, data[left]);\n          if (g(nxt)) {\n     \
    \       val = nxt;\n            ++left;\n          }\n        }\n        return\
    \ left - p2;\n      }\n      val = nxt;\n      ++left;\n    } while (__builtin_popcount(left)\
    \ > 1);\n    return n;\n  }\n\n  template <typename G>\n  int find_left(int right,\
    \ const G g) {\n    if (right <= 0) return -1;\n    right += p2;\n    for (int\
    \ i = height; i > 0; --i) {\n      propagate((right - 1) >> i);\n    }\n    Monoid\
    \ val = T::m_id();\n    do {\n      --right;\n      while (right > 1 && (right\
    \ & 1)) right >>= 1;\n      Monoid nxt = T::m_merge(data[right], val);\n     \
    \ if (!g(nxt)) {\n        while (right < p2) {\n          propagate(right);\n\
    \          right = (right << 1) + 1;\n          nxt = T::m_merge(data[right],\
    \ val);\n          if (g(nxt)) {\n            val = nxt;\n            --right;\n\
    \          }\n        }\n        return right - p2;\n      }\n      val = nxt;\n\
    \    } while (__builtin_popcount(right) > 1);\n    return -1;\n  }\n\n private:\n\
    \  int n;\n  int p2, height;\n  std::vector<Monoid> data;\n  std::vector<OperatorMonoid>\
    \ lazy;\n  LazySegmentTree(const LazySegmentTree &obj) : n(obj.n), p2(obj.p2),\
    \ height(obj.height), lazy(obj.lazy) {}\n\n  void apply_sub(const int idx, const\
    \ OperatorMonoid& val) {\n    data[idx] = T::apply(data[idx], val);\n    if (idx\
    \ < p2) lazy[idx] = T::o_merge(lazy[idx], val);\n  }\n\n  void propagate(const\
    \ int idx) {\n    // assert(1 <= idx && idx < p2);\n    apply_sub(idx << 1, lazy[idx]);\n\
    \    apply_sub((idx << 1) + 1, lazy[idx]);\n    lazy[idx] = T::o_id();\n  }\n\
    };\n\nnamespace monoid {\n\ntemplate <typename T>\nstruct RangeMinimumAndUpdateQuery\
    \ {\n  using Monoid = T;\n  using OperatorMonoid = T;\n  static constexpr Monoid\
    \ m_id() { return std::numeric_limits<Monoid>::max(); }\n  static constexpr OperatorMonoid\
    \ o_id() {\n    return std::numeric_limits<OperatorMonoid>::max();\n  }\n  static\
    \ Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::min(a, b);\n\
    \  }\n  static OperatorMonoid o_merge(const OperatorMonoid& a,\n             \
    \                   const OperatorMonoid& b) {\n    return b == o_id() ? a : b;\n\
    \  }\n  static Monoid apply(const Monoid& a, const OperatorMonoid& b) {\n    return\
    \ b == o_id() ? a : b;\n  }\n};\n\ntemplate <typename T>\nstruct RangeMaximumAndUpdateQuery\
    \ {\n  using Monoid = T;\n  using OperatorMonoid = T;\n  static constexpr Monoid\
    \ m_id() {\n    return std::numeric_limits<Monoid>::lowest();\n  }\n  static constexpr\
    \ OperatorMonoid o_id() {\n    return std::numeric_limits<OperatorMonoid>::lowest();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ std::max(a, b);\n  }\n  static OperatorMonoid o_merge(const OperatorMonoid&\
    \ a,\n                                const OperatorMonoid& b) {\n    return b\
    \ == o_id() ? a : b;\n  }\n  static Monoid apply(const Monoid& a, const OperatorMonoid&\
    \ b) {\n    return b == o_id()? a : b;\n  }\n};\n\ntemplate <typename T, T Inf>\n\
    struct RangeMinimumAndAddQuery {\n  using Monoid = T;\n  using OperatorMonoid\
    \ = T;\n  static constexpr Monoid m_id() { return Inf; }\n  static constexpr OperatorMonoid\
    \ o_id() { return 0; }\n  static Monoid m_merge(const Monoid& a, const Monoid&\
    \ b) {\n    return std::min(a, b);\n  }\n  static OperatorMonoid o_merge(const\
    \ OperatorMonoid& a,\n                                const OperatorMonoid& b)\
    \ {\n    return a + b;\n  }\n  static Monoid apply(const Monoid& a, const OperatorMonoid&\
    \ b) {\n    return a + b;\n  }\n};\n\ntemplate <typename T, T Inf>\nstruct RangeMaximumAndAddQuery\
    \ {\n  using Monoid = T;\n  using OperatorMonoid = T;\n  static constexpr Monoid\
    \ m_id() { return -Inf; }\n  static constexpr OperatorMonoid o_id() { return 0;\
    \ }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return std::max(a,\
    \ b);\n  }\n  static OperatorMonoid o_merge(const OperatorMonoid& a,\n       \
    \                         const OperatorMonoid& b) {\n    return a + b;\n  }\n\
    \  static Monoid apply(const Monoid& a, const OperatorMonoid& b) {\n    return\
    \ a + b;\n  }\n};\n\ntemplate <typename T>\nstruct RangeSumAndUpdateQuery {\n\
    \  using Monoid = struct { T sum; int len; };\n  using OperatorMonoid = T;\n \
    \ static std::vector<Monoid> init(const int n) {\n    return std::vector<Monoid>(n,\
    \ Monoid{0, 1});\n  }\n  static constexpr Monoid m_id() { return {0, 0}; }\n \
    \ static constexpr OperatorMonoid o_id() {\n    return std::numeric_limits<OperatorMonoid>::max();\n\
    \  }\n  static Monoid m_merge(const Monoid& a, const Monoid& b) {\n    return\
    \ Monoid{a.sum + b.sum, a.len + b.len};\n  }\n  static OperatorMonoid o_merge(const\
    \ OperatorMonoid& a,\n                                const OperatorMonoid& b)\
    \ {\n    return b == o_id() ? a : b;\n  }\n  static Monoid apply(const Monoid&\
    \ a, const OperatorMonoid& b) {\n    return Monoid{b == o_id() ? a.sum : b * a.len,\
    \ a.len};\n  }\n};\n\ntemplate <typename T>\nstruct RangeSumAndAddQuery {\n  using\
    \ Monoid = struct { T sum; int len; };\n  using OperatorMonoid = T;\n  static\
    \ std::vector<Monoid> init(const int n) {\n    return std::vector<Monoid>(n, Monoid{0,\
    \ 1});\n  }\n  static constexpr Monoid m_id() { return {0, 0}; }\n  static constexpr\
    \ OperatorMonoid o_id() { return 0; }\n  static Monoid m_merge(const Monoid& a,\
    \ const Monoid& b) {\n    return Monoid{a.sum + b.sum, a.len + b.len};\n  }\n\
    \  static OperatorMonoid o_merge(const OperatorMonoid& a,\n                  \
    \              const OperatorMonoid& b) {\n    return a + b;\n  }\n  static Monoid\
    \ apply(const Monoid& a, const OperatorMonoid& b) {\n    return Monoid{a.sum +\
    \ b * a.len, a.len};\n  }\n};\n\n}  // namespace monoid"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree/lazy_seg_leetcode.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segment_tree/lazy_seg_leetcode.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/lazy_seg_leetcode.hpp
- /library/data_structure/segment_tree/lazy_seg_leetcode.hpp.html
title: data_structure/segment_tree/lazy_seg_leetcode.hpp
---
