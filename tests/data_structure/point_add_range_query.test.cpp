#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
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

#include "../../data_structure/fenwick_tree.hpp"

void solve() {
  int N, Q;
  std::cin >> N >> Q;
  FenwickTree<long long> tree(N);
  while (Q--) {
    int op, a, b;
    std::cin >> op >> a >> b;

    if (op) {
      std::cout << tree.sum(a - 1, b - 1) << '\n';
    } else {
      tree.add(a - 1, b);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  solve();

  return 0;
}