#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
struct FenwickTree {
  std::vector<T> bit;
  int n;
  FenwickTree(int _n) : n(_n), bit(_n) {}
  FenwickTree(std::vector<T> a) {
    bit.resize(n, 0);
    for (int i = 0; i < (int)a.size(); i++) add(i, (int)a[i]);
  }
  T sum(int r) {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

  T sum(int l, int r) { return sum(r) - sum(l - 1); }

  void add(int idx, T delta) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
  }
};

void solve() {
  int N, Q;
  std::cin >> N >> Q;
  std::vector<long long> a(N);
  for (auto& x : a) std::cin >> x;
  FenwickTree<long long> tree(a);
  while (Q--) {
    int op, a, b;
    std::cin >> op >> a >> b;
    if (op) {
      std::cout << tree.sum(a, b - 1) << '\n';
    } else {
      tree.add(a, b);
    }
  }
}
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  solve();

  return 0;
}