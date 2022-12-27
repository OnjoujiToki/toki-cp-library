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
  bundledCode: "#line 1 \"data_structure/union_find.hpp\"\ntemplate <typename T>\n\
    struct DSU {\n  std::vector<T> f, siz;\n  DSU(int n) : f(n), siz(n, 1) { std::iota(f.begin(),\
    \ f.end(), 0); }\n  T leader(T x) {\n    while (x != f[x]) x = f[x] = f[f[x]];\n\
    \    return x;\n  }\n  bool same(T x, T y) { return leader(x) == leader(y); }\n\
    \  bool merge(T x, T y) {\n    x = leader(x);\n    y = leader(y);\n    if (x ==\
    \ y) return false;\n    siz[x] += siz[y];\n    f[y] = x;\n    return true;\n \
    \ }\n  T size(int x) { return siz[leader(x)]; }\n};\n"
  code: "template <typename T>\nstruct DSU {\n  std::vector<T> f, siz;\n  DSU(int\
    \ n) : f(n), siz(n, 1) { std::iota(f.begin(), f.end(), 0); }\n  T leader(T x)\
    \ {\n    while (x != f[x]) x = f[x] = f[f[x]];\n    return x;\n  }\n  bool same(T\
    \ x, T y) { return leader(x) == leader(y); }\n  bool merge(T x, T y) {\n    x\
    \ = leader(x);\n    y = leader(y);\n    if (x == y) return false;\n    siz[x]\
    \ += siz[y];\n    f[y] = x;\n    return true;\n  }\n  T size(int x) { return siz[leader(x)];\
    \ }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/union_find.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/union_find.hpp
layout: document
redirect_from:
- /library/data_structure/union_find.hpp
- /library/data_structure/union_find.hpp.html
title: data_structure/union_find.hpp
---
