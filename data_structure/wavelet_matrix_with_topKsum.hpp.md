---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://kopricky.github.io/code/DataStructure_Advanced/wavelet_matrix.html
  bundledCode: "#line 1 \"data_structure/wavelet_matrix_with_topKsum.hpp\"\n// wavelet\
    \ matrix topK sum \u4ED8\u304D\n\n// Wavelet matrix + range topK sum (small)\n\
    \n// https://kopricky.github.io/code/DataStructure_Advanced/wavelet_matrix.html\n\
    \n#include <algorithm>\n#include <vector>\n\nstruct BitRank {\n  // block: bit\
    \ \u5217\u3092\u7BA1\u7406, count: block \u3054\u3068\u306B\u7ACB\u3063\u3066\u3044\
    \u308B 1 \u306E\u6570\u3092\u7BA1\u7406\n  std::vector<unsigned long long> block;\n\
    \  std::vector<unsigned int> count;\n  BitRank() {}\n  void resize(const unsigned\
    \ int num) {\n    block.resize(((num + 1) >> 6) + 1, 0);\n    count.resize(block.size(),\
    \ 0);\n  }\n  // i \u30D3\u30C3\u30C8\u76EE\u3092 val(0,1) \u306B\u30BB\u30C3\u30C8\
    \n  void set(const unsigned int i, const unsigned long long val) {\n    block[i\
    \ >> 6] |= (val << (i & 63));\n  }\n  void build() {\n    for (unsigned int i\
    \ = 1; i < block.size(); i++) {\n      count[i] = count[i - 1] + __builtin_popcountll(block[i\
    \ - 1]);\n    }\n  }\n  // [0, i) \u30D3\u30C3\u30C8\u306E 1 \u306E\u6570\n  unsigned\
    \ int rank1(const unsigned int i) const {\n    return count[i >> 6] +\n      \
    \     __builtin_popcountll(block[i >> 6] & ((1ULL << (i & 63)) - 1ULL));\n  }\n\
    \  // [i, j) \u30D3\u30C3\u30C8\u306E 1 \u306E\u6570\n  unsigned int rank1(const\
    \ unsigned int i, const unsigned int j) const {\n    return rank1(j) - rank1(i);\n\
    \  }\n  // [0, i) \u30D3\u30C3\u30C8\u306E 0 \u306E\u6570\n  unsigned int rank0(const\
    \ unsigned int i) const { return i - rank1(i); }\n  // [i, j) \u30D3\u30C3\u30C8\
    \u306E 0 \u306E\u6570\n  unsigned int rank0(const unsigned int i, const unsigned\
    \ int j) const {\n    return rank0(j) - rank0(i);\n  }\n};\n\nclass WaveletMatrix\
    \ {\n private:\n  unsigned int height;\n  std::vector<BitRank> B;\n  std::vector<int>\
    \ pos;\n  std::vector<std::vector<long long>> rui;\n\n public:\n  WaveletMatrix()\
    \ {}\n  WaveletMatrix(std::vector<int> vec)\n      : WaveletMatrix(vec, *std::max_element(vec.begin(),\
    \ vec.end()) + 1) {}\n  // sigma:\u6587\u5B57\u306E\u7A2E\u985E\u6570\n  WaveletMatrix(std::vector<int>\
    \ vec, const unsigned int sigma) {\n    init(vec, sigma);\n  }\n  void init(std::vector<int>&\
    \ vec, const unsigned int sigma) {\n    height = (sigma == 1) ? 1 : (64 - __builtin_clzll(sigma\
    \ - 1));\n    B.resize(height), pos.resize(height);\n    std::vector<int> A =\
    \ vec;\n    rui.resize(height + 1);\n    for (unsigned int i = 0; i < height;\
    \ ++i) {\n      B[i].resize(vec.size());\n      for (unsigned int j = 0; j < vec.size();\
    \ ++j) {\n        B[i].set(j, get(vec[j], height - i - 1));\n      }\n      B[i].build();\n\
    \      auto it = stable_partition(vec.begin(), vec.end(), [&](int c) {\n     \
    \   return !get(c, height - i - 1);\n      });\n      pos[i] = it - vec.begin();\n\
    \    }\n\n    for (unsigned int i = 0; i <= height; ++i) {\n      rui[i].resize(A.size()\
    \ + 1);\n      for (int j = 1; j <= A.size(); j++) {\n        rui[i][j] = rui[i][j\
    \ - 1] + A[j - 1];\n      }\n      if (i == height) break;\n      std::stable_partition(A.begin(),\
    \ A.end(),\n                            [&](int c) { return !get(c, height - i\
    \ - 1); });\n    }\n  }\n  // val \u306E i \u30D3\u30C3\u30C8\u76EE\u306E\u5024\
    \u3092\u8FD4\u3059(0,1)\n  int get(const int val, const int i) { return val >>\
    \ i & 1; }\n  // [l, r) \u306E\u9593\u306B\u73FE\u308C\u308B\u5024 val \u306E\u6570\
    \n  int rank(const int val, const int l, const int r) {\n    return rank(val,\
    \ r) - rank(val, l);\n  }\n  // [0, i) \u306E\u9593\u306B\u73FE\u308C\u308B\u5024\
    \ val \u306E\u6570\n  int rank(int val, int i) {\n    int p = 0;\n    for (unsigned\
    \ int j = 0; j < height; ++j) {\n      if (get(val, height - j - 1)) {\n     \
    \   p = pos[j] + B[j].rank1(p);\n        i = pos[j] + B[j].rank1(i);\n      }\
    \ else {\n        p = B[j].rank0(p);\n        i = B[j].rank0(i);\n      }\n  \
    \  }\n    return i - p;\n  }\n  // [l, r) \u306E k(0,1,2...) \u756A\u76EE\u306B\
    \u5C0F\u3055\u3044\u5024\u3092\u8FD4\u3059\n  int quantile(int k, int l, int r)\
    \ {\n    int res = 0;\n    for (unsigned int i = 0; i < height; ++i) {\n     \
    \ const int j = B[i].rank0(l, r);\n      if (j > k) {\n        l = B[i].rank0(l);\n\
    \        r = B[i].rank0(r);\n      } else {\n        l = pos[i] + B[i].rank1(l);\n\
    \        r = pos[i] + B[i].rank1(r);\n        k -= j;\n        res |= (1 << (height\
    \ - i - 1));\n      }\n    }\n    return res;\n  }\n  long long topKsum(int k,\
    \ int l, int r) {\n    if (l == r) return 0LL;\n    long long res = 0;\n    int\
    \ atai = 0;\n    for (unsigned int i = 0; i < height; ++i) {\n      const int\
    \ j = B[i].rank0(l, r);\n      if (j > k) {\n        l = B[i].rank0(l);\n    \
    \    r = B[i].rank0(r);\n      } else {\n        int l2 = B[i].rank0(l);\n   \
    \     int r2 = B[i].rank0(r);\n        res += rui[i + 1][r2] - rui[i + 1][l2];\n\
    \n        l = pos[i] + B[i].rank1(l);\n        r = pos[i] + B[i].rank1(r);\n \
    \       k -= j;\n\n        atai |= (1 << (height - i - 1));\n      }\n    }\n\
    \    res += (long long)atai * k;\n    return res;\n  }\n  int rangefreq(const\
    \ int i, const int j, const int a, const int b, const int l,\n               \
    \ const int r, const int x) {\n    if (i == j || r <= a || b <= l) return 0;\n\
    \    const int mid = (l + r) >> 1;\n    if (a <= l && r <= b) {\n      return\
    \ j - i;\n    } else {\n      const int left =\n          rangefreq(B[x].rank0(i),\
    \ B[x].rank0(j), a, b, l, mid, x + 1);\n      const int right = rangefreq(pos[x]\
    \ + B[x].rank1(i),\n                                  pos[x] + B[x].rank1(j),\
    \ a, b, mid, r, x + 1);\n      return left + right;\n    }\n  }\n  // [l,r) \u3067\
    \u5024\u304C [a,b) \u5185\u306B\u542B\u307E\u308C\u308B\u6570\u3092\u8FD4\u3059\
    \n  int rangefreq(const int l, const int r, const int a, const int b) {\n    return\
    \ rangefreq(l, r, a, b, 0, 1 << height, 0);\n  }\n  int rangemin(const int i,\
    \ const int j, const int a, const int b, const int l,\n               const int\
    \ r, const int x, const int val) {\n    if (i == j || r <= a || b <= l) return\
    \ -1;\n    if (r - l == 1) return val;\n    const int mid = (l + r) >> 1;\n  \
    \  const int res =\n        rangemin(B[x].rank0(i), B[x].rank0(j), a, b, l, mid,\
    \ x + 1, val);\n    if (res < 0)\n      return rangemin(pos[x] + B[x].rank1(i),\
    \ pos[x] + B[x].rank1(j), a, b, mid,\n                      r, x + 1, val + (1\
    \ << (height - x - 1)));\n    else\n      return res;\n  }\n  // [l,r) \u3067\u5024\
    \u304C [a,b) \u5185\u306B\u6700\u5C0F\u306E\u6570\u3092\u8FD4\u3059(\u6570\u304C\
    \u5B58\u5728\u3057\u306A\u3044\u5834\u5408\u306F -1 \u3092\u8FD4\u3059)\n  int\
    \ rangemin(int l, int r, int a, int b) {\n    return rangemin(l, r, a, b, 0, 1\
    \ << height, 0, 0);\n  }\n};\n\ntemplate <typename T>\nclass OrthogonalRangeCount\
    \ {\n private:\n  using ptt = pair<T, T>;\n  const int sz;\n  std::vector<T> X,\
    \ Y;\n  WaveletMatrix wm;\n\n public:\n  OrthogonalRangeCount(std::vector<ptt>\
    \ candidate)\n      : sz((int)candidate.size()), X(sz), Y(sz) {\n    sort(candidate.begin(),\
    \ candidate.end());\n    std::vector<int> vec(sz);\n    for (int i = 0; i < sz;\
    \ ++i) {\n      X[i] = candidate[i].first, Y[i] = candidate[i].second;\n    }\n\
    \    sort(Y.begin(), Y.end());\n    Y.erase(unique(Y.begin(), Y.end()), Y.end());\n\
    \    for (int i = 0; i < sz; ++i) {\n      vec[i] = lower_bound(Y.begin(), Y.end(),\
    \ candidate[i].second) - Y.begin();\n    }\n    wm.init(vec, Y.size());\n  }\n\
    \  // [lx,rx) \xD7 [ly, ry) \u306E\u9577\u65B9\u5F62\u9818\u57DF\u306B\u542B\u307E\
    \u308C\u308B\u70B9\u306E\u6570\u3092\u7B54\u3048\u308B\n  int query(const T lx,\
    \ const T ly, const T rx, const T ry) {\n    const int lxid = lower_bound(X.begin(),\
    \ X.end(), lx) - X.begin();\n    const int rxid = lower_bound(X.begin(), X.end(),\
    \ rx) - X.begin();\n    const int lyid = lower_bound(Y.begin(), Y.end(), ly) -\
    \ Y.begin();\n    const int ryid = lower_bound(Y.begin(), Y.end(), ry) - Y.begin();\n\
    \    if (lxid >= rxid || lyid >= ryid) return 0;\n    return wm.rangefreq(lxid,\
    \ rxid, lyid, ryid);\n  }\n};\n\n"
  code: "// wavelet matrix topK sum \u4ED8\u304D\n\n// Wavelet matrix + range topK\
    \ sum (small)\n\n// https://kopricky.github.io/code/DataStructure_Advanced/wavelet_matrix.html\n\
    \n#include <algorithm>\n#include <vector>\n\nstruct BitRank {\n  // block: bit\
    \ \u5217\u3092\u7BA1\u7406, count: block \u3054\u3068\u306B\u7ACB\u3063\u3066\u3044\
    \u308B 1 \u306E\u6570\u3092\u7BA1\u7406\n  std::vector<unsigned long long> block;\n\
    \  std::vector<unsigned int> count;\n  BitRank() {}\n  void resize(const unsigned\
    \ int num) {\n    block.resize(((num + 1) >> 6) + 1, 0);\n    count.resize(block.size(),\
    \ 0);\n  }\n  // i \u30D3\u30C3\u30C8\u76EE\u3092 val(0,1) \u306B\u30BB\u30C3\u30C8\
    \n  void set(const unsigned int i, const unsigned long long val) {\n    block[i\
    \ >> 6] |= (val << (i & 63));\n  }\n  void build() {\n    for (unsigned int i\
    \ = 1; i < block.size(); i++) {\n      count[i] = count[i - 1] + __builtin_popcountll(block[i\
    \ - 1]);\n    }\n  }\n  // [0, i) \u30D3\u30C3\u30C8\u306E 1 \u306E\u6570\n  unsigned\
    \ int rank1(const unsigned int i) const {\n    return count[i >> 6] +\n      \
    \     __builtin_popcountll(block[i >> 6] & ((1ULL << (i & 63)) - 1ULL));\n  }\n\
    \  // [i, j) \u30D3\u30C3\u30C8\u306E 1 \u306E\u6570\n  unsigned int rank1(const\
    \ unsigned int i, const unsigned int j) const {\n    return rank1(j) - rank1(i);\n\
    \  }\n  // [0, i) \u30D3\u30C3\u30C8\u306E 0 \u306E\u6570\n  unsigned int rank0(const\
    \ unsigned int i) const { return i - rank1(i); }\n  // [i, j) \u30D3\u30C3\u30C8\
    \u306E 0 \u306E\u6570\n  unsigned int rank0(const unsigned int i, const unsigned\
    \ int j) const {\n    return rank0(j) - rank0(i);\n  }\n};\n\nclass WaveletMatrix\
    \ {\n private:\n  unsigned int height;\n  std::vector<BitRank> B;\n  std::vector<int>\
    \ pos;\n  std::vector<std::vector<long long>> rui;\n\n public:\n  WaveletMatrix()\
    \ {}\n  WaveletMatrix(std::vector<int> vec)\n      : WaveletMatrix(vec, *std::max_element(vec.begin(),\
    \ vec.end()) + 1) {}\n  // sigma:\u6587\u5B57\u306E\u7A2E\u985E\u6570\n  WaveletMatrix(std::vector<int>\
    \ vec, const unsigned int sigma) {\n    init(vec, sigma);\n  }\n  void init(std::vector<int>&\
    \ vec, const unsigned int sigma) {\n    height = (sigma == 1) ? 1 : (64 - __builtin_clzll(sigma\
    \ - 1));\n    B.resize(height), pos.resize(height);\n    std::vector<int> A =\
    \ vec;\n    rui.resize(height + 1);\n    for (unsigned int i = 0; i < height;\
    \ ++i) {\n      B[i].resize(vec.size());\n      for (unsigned int j = 0; j < vec.size();\
    \ ++j) {\n        B[i].set(j, get(vec[j], height - i - 1));\n      }\n      B[i].build();\n\
    \      auto it = stable_partition(vec.begin(), vec.end(), [&](int c) {\n     \
    \   return !get(c, height - i - 1);\n      });\n      pos[i] = it - vec.begin();\n\
    \    }\n\n    for (unsigned int i = 0; i <= height; ++i) {\n      rui[i].resize(A.size()\
    \ + 1);\n      for (int j = 1; j <= A.size(); j++) {\n        rui[i][j] = rui[i][j\
    \ - 1] + A[j - 1];\n      }\n      if (i == height) break;\n      std::stable_partition(A.begin(),\
    \ A.end(),\n                            [&](int c) { return !get(c, height - i\
    \ - 1); });\n    }\n  }\n  // val \u306E i \u30D3\u30C3\u30C8\u76EE\u306E\u5024\
    \u3092\u8FD4\u3059(0,1)\n  int get(const int val, const int i) { return val >>\
    \ i & 1; }\n  // [l, r) \u306E\u9593\u306B\u73FE\u308C\u308B\u5024 val \u306E\u6570\
    \n  int rank(const int val, const int l, const int r) {\n    return rank(val,\
    \ r) - rank(val, l);\n  }\n  // [0, i) \u306E\u9593\u306B\u73FE\u308C\u308B\u5024\
    \ val \u306E\u6570\n  int rank(int val, int i) {\n    int p = 0;\n    for (unsigned\
    \ int j = 0; j < height; ++j) {\n      if (get(val, height - j - 1)) {\n     \
    \   p = pos[j] + B[j].rank1(p);\n        i = pos[j] + B[j].rank1(i);\n      }\
    \ else {\n        p = B[j].rank0(p);\n        i = B[j].rank0(i);\n      }\n  \
    \  }\n    return i - p;\n  }\n  // [l, r) \u306E k(0,1,2...) \u756A\u76EE\u306B\
    \u5C0F\u3055\u3044\u5024\u3092\u8FD4\u3059\n  int quantile(int k, int l, int r)\
    \ {\n    int res = 0;\n    for (unsigned int i = 0; i < height; ++i) {\n     \
    \ const int j = B[i].rank0(l, r);\n      if (j > k) {\n        l = B[i].rank0(l);\n\
    \        r = B[i].rank0(r);\n      } else {\n        l = pos[i] + B[i].rank1(l);\n\
    \        r = pos[i] + B[i].rank1(r);\n        k -= j;\n        res |= (1 << (height\
    \ - i - 1));\n      }\n    }\n    return res;\n  }\n  long long topKsum(int k,\
    \ int l, int r) {\n    if (l == r) return 0LL;\n    long long res = 0;\n    int\
    \ atai = 0;\n    for (unsigned int i = 0; i < height; ++i) {\n      const int\
    \ j = B[i].rank0(l, r);\n      if (j > k) {\n        l = B[i].rank0(l);\n    \
    \    r = B[i].rank0(r);\n      } else {\n        int l2 = B[i].rank0(l);\n   \
    \     int r2 = B[i].rank0(r);\n        res += rui[i + 1][r2] - rui[i + 1][l2];\n\
    \n        l = pos[i] + B[i].rank1(l);\n        r = pos[i] + B[i].rank1(r);\n \
    \       k -= j;\n\n        atai |= (1 << (height - i - 1));\n      }\n    }\n\
    \    res += (long long)atai * k;\n    return res;\n  }\n  int rangefreq(const\
    \ int i, const int j, const int a, const int b, const int l,\n               \
    \ const int r, const int x) {\n    if (i == j || r <= a || b <= l) return 0;\n\
    \    const int mid = (l + r) >> 1;\n    if (a <= l && r <= b) {\n      return\
    \ j - i;\n    } else {\n      const int left =\n          rangefreq(B[x].rank0(i),\
    \ B[x].rank0(j), a, b, l, mid, x + 1);\n      const int right = rangefreq(pos[x]\
    \ + B[x].rank1(i),\n                                  pos[x] + B[x].rank1(j),\
    \ a, b, mid, r, x + 1);\n      return left + right;\n    }\n  }\n  // [l,r) \u3067\
    \u5024\u304C [a,b) \u5185\u306B\u542B\u307E\u308C\u308B\u6570\u3092\u8FD4\u3059\
    \n  int rangefreq(const int l, const int r, const int a, const int b) {\n    return\
    \ rangefreq(l, r, a, b, 0, 1 << height, 0);\n  }\n  int rangemin(const int i,\
    \ const int j, const int a, const int b, const int l,\n               const int\
    \ r, const int x, const int val) {\n    if (i == j || r <= a || b <= l) return\
    \ -1;\n    if (r - l == 1) return val;\n    const int mid = (l + r) >> 1;\n  \
    \  const int res =\n        rangemin(B[x].rank0(i), B[x].rank0(j), a, b, l, mid,\
    \ x + 1, val);\n    if (res < 0)\n      return rangemin(pos[x] + B[x].rank1(i),\
    \ pos[x] + B[x].rank1(j), a, b, mid,\n                      r, x + 1, val + (1\
    \ << (height - x - 1)));\n    else\n      return res;\n  }\n  // [l,r) \u3067\u5024\
    \u304C [a,b) \u5185\u306B\u6700\u5C0F\u306E\u6570\u3092\u8FD4\u3059(\u6570\u304C\
    \u5B58\u5728\u3057\u306A\u3044\u5834\u5408\u306F -1 \u3092\u8FD4\u3059)\n  int\
    \ rangemin(int l, int r, int a, int b) {\n    return rangemin(l, r, a, b, 0, 1\
    \ << height, 0, 0);\n  }\n};\n\ntemplate <typename T>\nclass OrthogonalRangeCount\
    \ {\n private:\n  using ptt = pair<T, T>;\n  const int sz;\n  std::vector<T> X,\
    \ Y;\n  WaveletMatrix wm;\n\n public:\n  OrthogonalRangeCount(std::vector<ptt>\
    \ candidate)\n      : sz((int)candidate.size()), X(sz), Y(sz) {\n    sort(candidate.begin(),\
    \ candidate.end());\n    std::vector<int> vec(sz);\n    for (int i = 0; i < sz;\
    \ ++i) {\n      X[i] = candidate[i].first, Y[i] = candidate[i].second;\n    }\n\
    \    sort(Y.begin(), Y.end());\n    Y.erase(unique(Y.begin(), Y.end()), Y.end());\n\
    \    for (int i = 0; i < sz; ++i) {\n      vec[i] = lower_bound(Y.begin(), Y.end(),\
    \ candidate[i].second) - Y.begin();\n    }\n    wm.init(vec, Y.size());\n  }\n\
    \  // [lx,rx) \xD7 [ly, ry) \u306E\u9577\u65B9\u5F62\u9818\u57DF\u306B\u542B\u307E\
    \u308C\u308B\u70B9\u306E\u6570\u3092\u7B54\u3048\u308B\n  int query(const T lx,\
    \ const T ly, const T rx, const T ry) {\n    const int lxid = lower_bound(X.begin(),\
    \ X.end(), lx) - X.begin();\n    const int rxid = lower_bound(X.begin(), X.end(),\
    \ rx) - X.begin();\n    const int lyid = lower_bound(Y.begin(), Y.end(), ly) -\
    \ Y.begin();\n    const int ryid = lower_bound(Y.begin(), Y.end(), ry) - Y.begin();\n\
    \    if (lxid >= rxid || lyid >= ryid) return 0;\n    return wm.rangefreq(lxid,\
    \ rxid, lyid, ryid);\n  }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/wavelet_matrix_with_topKsum.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/wavelet_matrix_with_topKsum.hpp
layout: document
redirect_from:
- /library/data_structure/wavelet_matrix_with_topKsum.hpp
- /library/data_structure/wavelet_matrix_with_topKsum.hpp.html
title: data_structure/wavelet_matrix_with_topKsum.hpp
---
