#pragma once
#include <cassert>
template <typename T>
struct FenwickTree {
  std::vector<T> bit;
  int n;
  FenwickTree(int _n) : n(_n), bit(_n) {}

  T sum(int r) {
    int ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

  T sum(int l, int r) {
    assert(l <= r);
    return sum(r) - sum(l - 1);
  }  // [l, r]

  void add(int idx, int delta) {
    for (; idx < n; idx = idx | (idx + 1)) bit[idx] += delta;
  }
};