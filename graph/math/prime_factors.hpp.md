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
  bundledCode: "#line 1 \"graph/math/prime_factors.hpp\"\n#include <cassert>\n#include\
    \ <cmath>\n#include <vector>\n\nstd::pair<std::vector<int>, std::vector<int>>\
    \ get_prime_factor_with_kinds(\n    int n) {\n  std::vector<int> prime_factors;\n\
    \  std::vector<int> cnt;  // number of i_th factor\n  for (int i = 2; i <= sqrt(n);\
    \ i++) {\n    if (n % i == 0) {\n      prime_factors.push_back(i);\n      cnt.push_back(0);\n\
    \      while (n % i == 0) n /= i, cnt[(int)prime_factors.size() - 1]++;\n    }\n\
    \  }\n  if (n > 1) prime_factors.push_back(n), cnt.push_back(1);\n  assert(prime_factors.size()\
    \ == cnt.size());\n  return {prime_factors, cnt};\n}\n\nstd::vector<int> get_prime_factor_without_kinds(int\
    \ n) {\n  std::vector<int> prime_factors;\n  for (int i = 2; i <= sqrt(n); i++)\
    \ {\n    if (n % i == 0) {\n      while (n % i == 0) n /= i, prime_factors.push_back(i);\n\
    \    }\n  }\n  if (n > 1) prime_factors.push_back(n);\n  return prime_factors;\n\
    }\n"
  code: "#include <cassert>\n#include <cmath>\n#include <vector>\n\nstd::pair<std::vector<int>,\
    \ std::vector<int>> get_prime_factor_with_kinds(\n    int n) {\n  std::vector<int>\
    \ prime_factors;\n  std::vector<int> cnt;  // number of i_th factor\n  for (int\
    \ i = 2; i <= sqrt(n); i++) {\n    if (n % i == 0) {\n      prime_factors.push_back(i);\n\
    \      cnt.push_back(0);\n      while (n % i == 0) n /= i, cnt[(int)prime_factors.size()\
    \ - 1]++;\n    }\n  }\n  if (n > 1) prime_factors.push_back(n), cnt.push_back(1);\n\
    \  assert(prime_factors.size() == cnt.size());\n  return {prime_factors, cnt};\n\
    }\n\nstd::vector<int> get_prime_factor_without_kinds(int n) {\n  std::vector<int>\
    \ prime_factors;\n  for (int i = 2; i <= sqrt(n); i++) {\n    if (n % i == 0)\
    \ {\n      while (n % i == 0) n /= i, prime_factors.push_back(i);\n    }\n  }\n\
    \  if (n > 1) prime_factors.push_back(n);\n  return prime_factors;\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/math/prime_factors.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/math/prime_factors.hpp
layout: document
redirect_from:
- /library/graph/math/prime_factors.hpp
- /library/graph/math/prime_factors.hpp.html
title: graph/math/prime_factors.hpp
---
