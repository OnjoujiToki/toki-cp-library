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
  bundledCode: "#line 1 \"graph/math/get_divisor.hpp\"\nstd::vector<int> get_divisors(int\
    \ x) {\n  std::vector<int> res;\n  for (int i = 1; i <= x / i; i++)\n    if (x\
    \ % i == 0) {\n      res.push_back(i);\n      if (i != x / i) res.push_back(x\
    \ / i);\n    }\n  std::sort(res.begin(), res.end());\n  return res;\n}\n"
  code: "std::vector<int> get_divisors(int x) {\n  std::vector<int> res;\n  for (int\
    \ i = 1; i <= x / i; i++)\n    if (x % i == 0) {\n      res.push_back(i);\n  \
    \    if (i != x / i) res.push_back(x / i);\n    }\n  std::sort(res.begin(), res.end());\n\
    \  return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/math/get_divisor.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/math/get_divisor.hpp
layout: document
redirect_from:
- /library/graph/math/get_divisor.hpp
- /library/graph/math/get_divisor.hpp.html
title: graph/math/get_divisor.hpp
---
