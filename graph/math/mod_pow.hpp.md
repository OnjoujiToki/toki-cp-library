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
  bundledCode: "#line 1 \"graph/math/mod_pow.hpp\"\nlong long mod_pow(long long x,\
    \ int n, int p) {\n  long long ret = 1;\n  while (n) {\n    if (n & 1) (ret *=\
    \ x) %= p;\n    (x *= x) %= p;\n    n >>= 1;\n  }\n  return ret;\n}\n"
  code: "long long mod_pow(long long x, int n, int p) {\n  long long ret = 1;\n  while\
    \ (n) {\n    if (n & 1) (ret *= x) %= p;\n    (x *= x) %= p;\n    n >>= 1;\n \
    \ }\n  return ret;\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/math/mod_pow.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/math/mod_pow.hpp
layout: document
redirect_from:
- /library/graph/math/mod_pow.hpp
- /library/graph/math/mod_pow.hpp.html
title: graph/math/mod_pow.hpp
---
