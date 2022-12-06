#pragma once
#define PROBLEM \
  "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"
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

#include "../../data_structure//segment_tree/zkw_seg_tree.hpp"

void solve() {
  int n;
  std::cin >> n;
  int q;
  std::cin >> q;
  std::vector<int> a(n, std::numeric_limits<int>::max());

  SegmentTree<monoid::RangeMinimumQuery<int>> st(a);
  while (q--) {
    int op;
    std::cin >> op;
    if (!op) {
      int idx, val;
      std::cin >> idx >> val;
      st.set(idx, val);

    } else {
      int l, r;
      std::cin >> l >> r;
      std::cout << st.get(l, r + 1) << '\n';
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);

  solve();

  return 0;
}