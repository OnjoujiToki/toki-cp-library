#include <cstdint>
// https://knshnb.github.io/competitive_library/src/DataStructure/WaveletMatrix.hpp
int popcount(int x) { return __builtin_popcount(x); }
int popcount(long long x) { return __builtin_popcountll(x); }

template <class block_type = std::uint64_t>
struct BitVector {
  static constexpr size_t b = sizeof(block_type) * CHAR_BIT;  // blockのサイズ
  int n;
  std::vector<block_type> bit;
  std::vector<int> acc;
  BitVector() {}
  BitVector(int n_) : n(n_), bit(n / b + 1), acc(n / b + 1) {}
  template <bool x = 1>
  void set(size_t i) {
    if (x)
      bit[i / b] |= (block_type)1 << (i % b);
    else
      bit[i / b] &= ~((block_type)1 << (i % b));
  }
  void build() {
    for (int i = 0; i < (int)acc.size() - 1; i++) {
      acc[i + 1] = acc[i] + popcount(bit[i]);
    }
  }
  // [0, i)内のxの個数
  template <bool x>
  int rank(size_t i) {
    if (x)
      return acc[i / b] + (i % b ? popcount(bit[i / b] << (b - i % b)) : 0);
    else
      return i - rank<1>(i);
  }
  // j番目のxのindex
  template <bool x>
  int select(size_t j) {
    int ok = n, ng = -1;
    while (std::abs(ok - ng) > 1) {
      int mid = (ok + ng) / 2;
      (rank<x>(mid + 1) > j ? ok : ng) = mid;
    }
    return ok;
  }
};

template <class T, int maxlog = 31, class block_type = std::uint64_t>
struct WaveletMatrix {
  static_assert((T(1) << (maxlog - 1)) > 0);
  using bv_type = BitVector<block_type>;
  std::array<bv_type, maxlog> bvs;  // [maxlog, n]の01行列
  std::array<int, maxlog> offset = {};  // 各列でbitが0になっている要素の数

  WaveletMatrix(const std::vector<T>& a) {
    std::vector<T> cur_data = a;
    for (int k = maxlog - 1; k >= 0; k--) {  // 上位bitから見る
      std::vector<T> zero, one;
      bvs[k] = bv_type(a.size());
      for (int i = 0; i < a.size(); i++) {
        bool bit = cur_data[i] >> k & 1;
        if (bit)
          one.push_back(cur_data[i]), bvs[k].template set<1>(i);
        else
          zero.push_back(cur_data[i]);
      }
      offset[k] = zero.size();
      cur_data = std::move(zero);
      cur_data.insert(cur_data.end(), one.begin(), one.end());
      bvs[k].build();
    }
  }
  // [l, r)の{x未満の個数, xの個数, xより大の個数}
  std::array<int, 3> rank_3way(int l, int r, int x) {
    int lt = 0, eq = r - l, gt = 0;
    for (int k = maxlog - 1; k >= 0; k--) {
      int prv_num = r - l;
      if (x >> k & 1) {
        l = offset[k] + bvs[k].template rank<1>(l);
        r = offset[k] + bvs[k].template rank<1>(r);
        lt += prv_num - (r - l);
      } else {
        l = bvs[k].template rank<0>(l);
        r = bvs[k].template rank<0>(r);
        gt += prv_num - (r - l);
      }
      eq -= prv_num - (r - l);
    }
    return {lt, eq, gt};
  }
  // [l, r)内の(小さい方から)j番目(0-index)の数
  int quantile(int l, int r, int j) {
    assert(j < r - l);
    T ret = 0;
    for (int k = maxlog - 1; k >= 0; k--) {
      int zl = bvs[k].template rank<0>(l);
      int zr = bvs[k].template rank<0>(r);
      if (zr - zl > j) {  // kビット目は0
        l = zl;
        r = zr;
      } else {  // kビット目は1
        l = offset[k] + (l - zl);
        r = offset[k] + (r - zr);
        ret |= (T)1 << k;
        j -= zr - zl;
      }
    }
    return ret;
  }
};