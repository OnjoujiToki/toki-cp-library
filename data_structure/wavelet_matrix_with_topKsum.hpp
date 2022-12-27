// wavelet matrix topK sum 付き

// Wavelet matrix + range topK sum (small)

// https://kopricky.github.io/code/DataStructure_Advanced/wavelet_matrix.html

#include <algorithm>
#include <vector>

struct BitRank {
  // block: bit 列を管理, count: block ごとに立っている 1 の数を管理
  std::vector<unsigned long long> block;
  std::vector<unsigned int> count;
  BitRank() {}
  void resize(const unsigned int num) {
    block.resize(((num + 1) >> 6) + 1, 0);
    count.resize(block.size(), 0);
  }
  // i ビット目を val(0,1) にセット
  void set(const unsigned int i, const unsigned long long val) {
    block[i >> 6] |= (val << (i & 63));
  }
  void build() {
    for (unsigned int i = 1; i < block.size(); i++) {
      count[i] = count[i - 1] + __builtin_popcountll(block[i - 1]);
    }
  }
  // [0, i) ビットの 1 の数
  unsigned int rank1(const unsigned int i) const {
    return count[i >> 6] +
           __builtin_popcountll(block[i >> 6] & ((1ULL << (i & 63)) - 1ULL));
  }
  // [i, j) ビットの 1 の数
  unsigned int rank1(const unsigned int i, const unsigned int j) const {
    return rank1(j) - rank1(i);
  }
  // [0, i) ビットの 0 の数
  unsigned int rank0(const unsigned int i) const { return i - rank1(i); }
  // [i, j) ビットの 0 の数
  unsigned int rank0(const unsigned int i, const unsigned int j) const {
    return rank0(j) - rank0(i);
  }
};

class WaveletMatrix {
 private:
  unsigned int height;
  std::vector<BitRank> B;
  std::vector<int> pos;
  std::vector<std::vector<long long>> rui;

 public:
  WaveletMatrix() {}
  WaveletMatrix(std::vector<int> vec)
      : WaveletMatrix(vec, *std::max_element(vec.begin(), vec.end()) + 1) {}
  // sigma:文字の種類数
  WaveletMatrix(std::vector<int> vec, const unsigned int sigma) {
    init(vec, sigma);
  }
  void init(std::vector<int>& vec, const unsigned int sigma) {
    height = (sigma == 1) ? 1 : (64 - __builtin_clzll(sigma - 1));
    B.resize(height), pos.resize(height);
    std::vector<int> A = vec;
    rui.resize(height + 1);
    for (unsigned int i = 0; i < height; ++i) {
      B[i].resize(vec.size());
      for (unsigned int j = 0; j < vec.size(); ++j) {
        B[i].set(j, get(vec[j], height - i - 1));
      }
      B[i].build();
      auto it = stable_partition(vec.begin(), vec.end(), [&](int c) {
        return !get(c, height - i - 1);
      });
      pos[i] = it - vec.begin();
    }

    for (unsigned int i = 0; i <= height; ++i) {
      rui[i].resize(A.size() + 1);
      for (int j = 1; j <= A.size(); j++) {
        rui[i][j] = rui[i][j - 1] + A[j - 1];
      }
      if (i == height) break;
      std::stable_partition(A.begin(), A.end(),
                            [&](int c) { return !get(c, height - i - 1); });
    }
  }
  // val の i ビット目の値を返す(0,1)
  int get(const int val, const int i) { return val >> i & 1; }
  // [l, r) の間に現れる値 val の数
  int rank(const int val, const int l, const int r) {
    return rank(val, r) - rank(val, l);
  }
  // [0, i) の間に現れる値 val の数
  int rank(int val, int i) {
    int p = 0;
    for (unsigned int j = 0; j < height; ++j) {
      if (get(val, height - j - 1)) {
        p = pos[j] + B[j].rank1(p);
        i = pos[j] + B[j].rank1(i);
      } else {
        p = B[j].rank0(p);
        i = B[j].rank0(i);
      }
    }
    return i - p;
  }
  // [l, r) の k(0,1,2...) 番目に小さい値を返す
  int quantile(int k, int l, int r) {
    int res = 0;
    for (unsigned int i = 0; i < height; ++i) {
      const int j = B[i].rank0(l, r);
      if (j > k) {
        l = B[i].rank0(l);
        r = B[i].rank0(r);
      } else {
        l = pos[i] + B[i].rank1(l);
        r = pos[i] + B[i].rank1(r);
        k -= j;
        res |= (1 << (height - i - 1));
      }
    }
    return res;
  }
  long long topKsum(int k, int l, int r) {
    if (l == r) return 0LL;
    long long res = 0;
    int atai = 0;
    for (unsigned int i = 0; i < height; ++i) {
      const int j = B[i].rank0(l, r);
      if (j > k) {
        l = B[i].rank0(l);
        r = B[i].rank0(r);
      } else {
        int l2 = B[i].rank0(l);
        int r2 = B[i].rank0(r);
        res += rui[i + 1][r2] - rui[i + 1][l2];

        l = pos[i] + B[i].rank1(l);
        r = pos[i] + B[i].rank1(r);
        k -= j;

        atai |= (1 << (height - i - 1));
      }
    }
    res += (long long)atai * k;
    return res;
  }
  int rangefreq(const int i, const int j, const int a, const int b, const int l,
                const int r, const int x) {
    if (i == j || r <= a || b <= l) return 0;
    const int mid = (l + r) >> 1;
    if (a <= l && r <= b) {
      return j - i;
    } else {
      const int left =
          rangefreq(B[x].rank0(i), B[x].rank0(j), a, b, l, mid, x + 1);
      const int right = rangefreq(pos[x] + B[x].rank1(i),
                                  pos[x] + B[x].rank1(j), a, b, mid, r, x + 1);
      return left + right;
    }
  }
  // [l,r) で値が [a,b) 内に含まれる数を返す
  int rangefreq(const int l, const int r, const int a, const int b) {
    return rangefreq(l, r, a, b, 0, 1 << height, 0);
  }
  int rangemin(const int i, const int j, const int a, const int b, const int l,
               const int r, const int x, const int val) {
    if (i == j || r <= a || b <= l) return -1;
    if (r - l == 1) return val;
    const int mid = (l + r) >> 1;
    const int res =
        rangemin(B[x].rank0(i), B[x].rank0(j), a, b, l, mid, x + 1, val);
    if (res < 0)
      return rangemin(pos[x] + B[x].rank1(i), pos[x] + B[x].rank1(j), a, b, mid,
                      r, x + 1, val + (1 << (height - x - 1)));
    else
      return res;
  }
  // [l,r) で値が [a,b) 内に最小の数を返す(数が存在しない場合は -1 を返す)
  int rangemin(int l, int r, int a, int b) {
    return rangemin(l, r, a, b, 0, 1 << height, 0, 0);
  }
};

template <typename T>
class OrthogonalRangeCount {
 private:
  using ptt = pair<T, T>;
  const int sz;
  std::vector<T> X, Y;
  WaveletMatrix wm;

 public:
  OrthogonalRangeCount(std::vector<ptt> candidate)
      : sz((int)candidate.size()), X(sz), Y(sz) {
    sort(candidate.begin(), candidate.end());
    std::vector<int> vec(sz);
    for (int i = 0; i < sz; ++i) {
      X[i] = candidate[i].first, Y[i] = candidate[i].second;
    }
    sort(Y.begin(), Y.end());
    Y.erase(unique(Y.begin(), Y.end()), Y.end());
    for (int i = 0; i < sz; ++i) {
      vec[i] = lower_bound(Y.begin(), Y.end(), candidate[i].second) - Y.begin();
    }
    wm.init(vec, Y.size());
  }
  // [lx,rx) × [ly, ry) の長方形領域に含まれる点の数を答える
  int query(const T lx, const T ly, const T rx, const T ry) {
    const int lxid = lower_bound(X.begin(), X.end(), lx) - X.begin();
    const int rxid = lower_bound(X.begin(), X.end(), rx) - X.begin();
    const int lyid = lower_bound(Y.begin(), Y.end(), ly) - Y.begin();
    const int ryid = lower_bound(Y.begin(), Y.end(), ry) - Y.begin();
    if (lxid >= rxid || lyid >= ryid) return 0;
    return wm.rangefreq(lxid, rxid, lyid, ryid);
  }
};

