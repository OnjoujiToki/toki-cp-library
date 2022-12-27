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
  bundledCode: "#line 1 \"geometry/circle.hpp\"\nstruct Circle {\n  int x, y, r;\n\
    \n  Circle(int x, int y, int r) : x(x), y(y), r(r) {}\n  Circle() : Circle(0,\
    \ 0, 0) {}  // \u8C03\u7528\u6709\u53C2\u6570\u7684\u6784\u9020\u51FD\u6570\n\
    };\n\nbool intersect(const Circle& c1, const Circle& c2) {\n  if (c1.x == c2.x\
    \ and c1.y == c2.y) {\n    return c1.r == c2.r;\n  }\n  long long d =\n      1LL\
    \ * (c1.x - c2.x) * (c1.x - c2.x) + 1LL * (c1.y - c2.y) * (c1.y - c2.y);\n  return\
    \ d <= 1LL * (c1.r + c2.r) * (c1.r + c2.r);\n}\n\nbool on_circle(const Circle&\
    \ c, int x_p, int y_p) {\n  long long d =\n      1LL * (x_p - c.x) * (x_p - c.x)\
    \ + 1LL * (y_p - c.y) * (y_p - c.y);\n  return d == 1LL * c.r * c.r;\n}\n"
  code: "struct Circle {\n  int x, y, r;\n\n  Circle(int x, int y, int r) : x(x),\
    \ y(y), r(r) {}\n  Circle() : Circle(0, 0, 0) {}  // \u8C03\u7528\u6709\u53C2\u6570\
    \u7684\u6784\u9020\u51FD\u6570\n};\n\nbool intersect(const Circle& c1, const Circle&\
    \ c2) {\n  if (c1.x == c2.x and c1.y == c2.y) {\n    return c1.r == c2.r;\n  }\n\
    \  long long d =\n      1LL * (c1.x - c2.x) * (c1.x - c2.x) + 1LL * (c1.y - c2.y)\
    \ * (c1.y - c2.y);\n  return d <= 1LL * (c1.r + c2.r) * (c1.r + c2.r);\n}\n\n\
    bool on_circle(const Circle& c, int x_p, int y_p) {\n  long long d =\n      1LL\
    \ * (x_p - c.x) * (x_p - c.x) + 1LL * (y_p - c.y) * (y_p - c.y);\n  return d ==\
    \ 1LL * c.r * c.r;\n}"
  dependsOn: []
  isVerificationFile: false
  path: geometry/circle.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: geometry/circle.hpp
layout: document
redirect_from:
- /library/geometry/circle.hpp
- /library/geometry/circle.hpp.html
title: geometry/circle.hpp
---
