#pragma once
// credit emthrm.github.io/library
template <typename T>
struct SegmentTree {
  using Monoid = typename T::Monoid;

  explicit SegmentTree(int n) : SegmentTree(std::vector<Monoid>(n, T::id())) {}

  explicit SegmentTree(const std::vector<Monoid>& a) : n(a.size()), sz(1) {
    while (sz < n) sz <<= 1;
    data.assign(sz << 1, T::id());
    std::copy(a.begin(), a.end(), data.begin() + sz);
    for (int i = sz - 1; i > 0; --i) {
      data[i] = T::merge(data[i << 1], data[(i << 1) + 1]);
    }
  }

  void set(int idx, const Monoid val) {
    idx += sz;
    data[idx] = val;
    while (idx >>= 1)
      data[idx] = T::merge(data[idx << 1], data[(idx << 1) + 1]);
  }

  Monoid get(int left, int right) const {
    Monoid res_l = T::id(), res_r = T::id();
    for (left += sz, right += sz; left < right; left >>= 1, right >>= 1) {
      if (left & 1) res_l = T::merge(res_l, data[left++]);
      if (right & 1) res_r = T::merge(data[--right], res_r);
    }
    return T::merge(res_l, res_r);
  }

  Monoid operator[](const int idx) const { return data[idx + sz]; }

 private:
  const int n;
  int sz;  // sz + 原数组坐标 = 线段树里的编号，1 based
  std::vector<Monoid> data;
};

namespace monoid {

template <typename T>
struct RangeMinimumQuery {
  using Monoid = T;
  static constexpr Monoid id() { return std::numeric_limits<Monoid>::max(); }
  static Monoid merge(const Monoid& a, const Monoid& b) {
    return std::min(a, b);
  }
};

template <typename T>
struct RangeMaximumQuery {
  using Monoid = T;
  static constexpr Monoid id() { return std::numeric_limits<Monoid>::lowest(); }
  static Monoid merge(const Monoid& a, const Monoid& b) {
    return std::max(a, b);
  }
};

template <typename T>
struct RangeSumQuery {
  using Monoid = T;
  static constexpr Monoid id() { return 0; }
  static Monoid merge(const Monoid& a, const Monoid& b) { return a + b; }
};

}  // namespace monoid