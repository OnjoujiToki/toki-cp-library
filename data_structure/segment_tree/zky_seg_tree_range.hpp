#pragma once
// credit: emthrm.github.io/library
#include <algorithm>
#include <limits>
#include <vector>

template <typename T>
struct LazySegmentTree {
  using Monoid = typename T::Monoid;
  using LazyMonoid = typename T::LazyMonoid;

  explicit LazySegmentTree(const int n)
      : LazySegmentTree(std::vector<Monoid>(n, T::m_id())) {}

  explicit LazySegmentTree(const std::vector<Monoid>& a)
      : n(a.size()), height(0) {
    while ((1 << height) < n) ++height;
    sz = 1 << height;
    lazy.assign(sz, T::lazy_id());
    data.assign(sz << 1, T::m_id());
    std::copy(a.begin(), a.end(), data.begin() + sz);
    for (int i = sz - 1; i > 0; --i) {
      data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);
    }
  }

  void set(int idx, const Monoid val) {
    idx += sz;
    for (int i = height; i > 0; --i) {
      propagate(idx >> i);
    }
    data[idx] = val;
    for (int i = 1; i <= height; ++i) {
      const int current_idx = idx >> i;
      data[current_idx] =
          T::m_merge(data[current_idx << 1], data[(current_idx << 1) + 1]);
    }
  }

  void apply(int idx, const LazyMonoid val) {
    idx += sz;
    for (int i = height; i > 0; --i) {
      propagate(idx >> i);
    }
    data[idx] = T::apply(data[idx], val);
    for (int i = 1; i <= height; ++i) {
      const int current_idx = idx >> i;
      data[current_idx] =
          T::m_merge(data[current_idx << 1], data[(current_idx << 1) + 1]);
    }
  }

  void apply(int left, int right, const LazyMonoid val) {
    if (right <= left) return;
    left += sz;
    right += sz;
    const int ctz_left = __builtin_ctz(left);
    for (int i = height; i > ctz_left; --i) {
      propagate(left >> i);
    }
    const int ctz_right = __builtin_ctz(right);
    for (int i = height; i > ctz_right; --i) {
      propagate(right >> i);
    }
    for (int l = left, r = right; l < r; l >>= 1, r >>= 1) {
      if (l & 1) apply_sub(l++, val);
      if (r & 1) apply_sub(--r, val);
    }
    for (int i = left >> (ctz_left + 1); i > 0; i >>= 1) {
      data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);
    }
    for (int i = right >> (ctz_right + 1); i > 0; i >>= 1) {
      data[i] = T::m_merge(data[i << 1], data[(i << 1) + 1]);
    }
  }

  Monoid get(int left, int right) {
    if (right <= left) return T::m_id();
    left += sz;
    right += sz;
    const int ctz_left = __builtin_ctz(left);
    for (int i = height; i > ctz_left; --i) {
      propagate(left >> i);
    }
    const int ctz_right = __builtin_ctz(right);
    for (int i = height; i > ctz_right; --i) {
      propagate(right >> i);
    }
    Monoid res_l = T::m_id(), res_r = T::m_id();
    for (; left < right; left >>= 1, right >>= 1) {
      if (left & 1) res_l = T::m_merge(res_l, data[left++]);
      if (right & 1) res_r = T::m_merge(data[--right], res_r);
    }
    return T::m_merge(res_l, res_r);
  }

  Monoid operator[](const int idx) {
    const int node = idx + sz;
    for (int i = height; i > 0; --i) {
      propagate(node >> i);
    }
    return data[node];
  }

  template <typename G>
  int find_right(int left, const G g) {
    if (left >= n) return n;
    left += sz;
    for (int i = height; i > 0; --i) {
      propagate(left >> i);
    }
    Monoid val = T::m_id();
    do {
      while (!(left & 1)) left >>= 1;
      Monoid nxt = T::m_merge(val, data[left]);
      if (!g(nxt)) {
        while (left < sz) {
          propagate(left);
          left <<= 1;
          nxt = T::m_merge(val, data[left]);
          if (g(nxt)) {
            val = nxt;
            ++left;
          }
        }
        return left - sz;
      }
      val = nxt;
      ++left;
    } while (__builtin_popcount(left) > 1);
    return n;
  }

  template <typename G>
  int find_left(int right, const G g) {
    if (right <= 0) return -1;
    right += sz;
    for (int i = height; i > 0; --i) {
      propagate((right - 1) >> i);
    }
    Monoid val = T::m_id();
    do {
      --right;
      while (right > 1 && (right & 1)) right >>= 1;
      Monoid nxt = T::m_merge(data[right], val);
      if (!g(nxt)) {
        while (right < sz) {
          propagate(right);
          right = (right << 1) + 1;
          nxt = T::m_merge(data[right], val);
          if (g(nxt)) {
            val = nxt;
            --right;
          }
        }
        return right - sz;
      }
      val = nxt;
    } while (__builtin_popcount(right) > 1);
    return -1;
  }

  const int n;
  int sz, height;
  std::vector<Monoid> data;
  std::vector<LazyMonoid> lazy;

  void apply_sub(const int idx, const LazyMonoid& val) {
    data[idx] = T::apply(data[idx], val);
    if (idx < sz) lazy[idx] = T::lazy_merge(lazy[idx], val);
  }

  void propagate(const int idx) {
    apply_sub(idx << 1, lazy[idx]);
    apply_sub((idx << 1) + 1, lazy[idx]);
    lazy[idx] = T::lazy_id();
  }
};

namespace monoid {

template <typename T>
struct RangeMinimumAndUpdateQuery {
  using Monoid = T;
  using LazyMonoid = T;
  static constexpr Monoid m_id() { return std::numeric_limits<Monoid>::max(); }
  static constexpr LazyMonoid lazy_id() {
    return std::numeric_limits<LazyMonoid>::max();
  }
  static Monoid m_merge(const Monoid& a, const Monoid& b) {
    return std::min(a, b);
  }
  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {
    return b == lazy_id() ? a : b;
  }
  static Monoid apply(const Monoid& a, const LazyMonoid& b) {
    return b == lazy_id() ? a : b;
  }
};

template <typename T>
struct RangeMaximumAndUpdateQuery {
  using Monoid = T;
  using LazyMonoid = T;
  static constexpr Monoid m_id() {
    return std::numeric_limits<Monoid>::lowest();
  }
  static constexpr LazyMonoid lazy_id() {
    return std::numeric_limits<LazyMonoid>::lowest();
  }
  static Monoid m_merge(const Monoid& a, const Monoid& b) {
    return std::max(a, b);
  }
  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {
    return b == lazy_id() ? a : b;
  }
  static Monoid apply(const Monoid& a, const LazyMonoid& b) {
    return b == lazy_id() ? a : b;
  }
};

template <typename T, T Inf>
struct RangeMinimumAndAddQuery {
  using Monoid = T;
  using LazyMonoid = T;
  static constexpr Monoid m_id() { return Inf; }
  static constexpr LazyMonoid lazy_id() { return 0; }
  static Monoid m_merge(const Monoid& a, const Monoid& b) {
    return std::min(a, b);
  }
  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {
    return a + b;
  }
  static Monoid apply(const Monoid& a, const LazyMonoid& b) { return a + b; }
};

template <typename T, T Inf>
struct RangeMaximumAndAddQuery {
  using Monoid = T;
  using LazyMonoid = T;
  static constexpr Monoid m_id() { return -Inf; }
  static constexpr LazyMonoid lazy_id() { return 0; }
  static Monoid m_merge(const Monoid& a, const Monoid& b) {
    return std::max(a, b);
  }
  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {
    return a + b;
  }
  static Monoid apply(const Monoid& a, const LazyMonoid& b) { return a + b; }
};

template <typename T>
struct RangeSumAndUpdateQuery {
  using Monoid = struct {
    T sum;
    int len;
  };
  using LazyMonoid = T;
  static std::vector<Monoid> init(const int n) {
    return std::vector<Monoid>(n, Monoid{0, 1});
  }
  static constexpr Monoid m_id() { return {0, 0}; }
  static constexpr LazyMonoid lazy_id() {
    return std::numeric_limits<LazyMonoid>::max();
  }
  static Monoid m_merge(const Monoid& a, const Monoid& b) {
    return Monoid{a.sum + b.sum, a.len + b.len};
  }
  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {
    return b == lazy_id() ? a : b;
  }
  static Monoid apply(const Monoid& a, const LazyMonoid& b) {
    return Monoid{b == lazy_id() ? a.sum : b * a.len, a.len};
  }
};

template <typename T>
struct RangeSumAndAddQuery {
  using Monoid = struct {
    T sum;
    int len;
  };
  using LazyMonoid = T;
  static std::vector<Monoid> init(const int n) {
    return std::vector<Monoid>(n, Monoid{0, 1});
  }
  static constexpr Monoid m_id() { return {0, 0}; }
  static constexpr LazyMonoid lazy_id() { return 0; }
  static Monoid m_merge(const Monoid& a, const Monoid& b) {
    return Monoid{a.sum + b.sum, a.len + b.len};
  }
  static LazyMonoid lazy_merge(const LazyMonoid& a, const LazyMonoid& b) {
    return a + b;
  }
  static Monoid apply(const Monoid& a, const LazyMonoid& b) {
    return Monoid{a.sum + b * a.len, a.len};
  }
};

}  // namespace monoid