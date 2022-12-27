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
  bundledCode: "#line 1 \"data_structure/chtholly_tree.hpp\"\n#include <algorithm>\n\
    #include <set>\n#include <vector>\n\nstruct ChthollyNode {\n  int l, r;\n  mutable\
    \ int v;\n  ChthollyNode(int l, int r, int v) : l(l), r(r), v(v) {}\n  bool operator<(const\
    \ ChthollyNode &o) const { return l < o.l; }\n};\n\nstd::set<ChthollyNode> tr;\n\
    std::set<ChthollyNode>::iterator split(int pos) {\n  auto it = tr.lower_bound(ChthollyNode(pos,\
    \ 0, 0));\n  if (it != tr.end() && it->l == pos) return it;\n  it--;\n  int l\
    \ = it->l, r = it->r, v = it->v;\n  tr.erase(it);\n  tr.insert(ChthollyNode(l,\
    \ pos - 1, v));\n  return tr.insert(ChthollyNode(pos, r, v)).first;\n}\n\n// range\
    \ add\nvoid add(int l, int r, int v) {  // [l, r]\n  auto end = split(r + 1);\n\
    \  for (auto it = split(l); it != end; it++) it->v += v;\n}\n\n// range assign\n\
    void assign(int l, int r, int v) {\n  auto end = split(r + 1), begin = split(l);\
    \  // \u987A\u5E8F\u4E0D\u80FD\u98A0\u5012\uFF0C\u5426\u5219\u53EF\u80FDRE\n \
    \ tr.erase(begin, end);                       // \u6E05\u9664\u4E00\u7CFB\u5217\
    \u8282\u70B9\n  tr.insert(ChthollyNode(l, r, v));           // \u63D2\u5165\u65B0\
    \u7684\u8282\u70B9\n}\n\n// range kth\nint kth(int l, int r, int k) {\n  auto\
    \ end = split(r + 1);\n  std::vector<std::pair<int, int>> v;  // \u8FD9\u4E2A\
    pair\u91CC\u5B58\u8282\u70B9\u7684\u503C\u548C\u533A\u95F4\u957F\u5EA6\n  for\
    \ (auto it = split(l); it != end; it++)\n    v.emplace_back(it->v, it->r - it->l\
    \ + 1);\n  std::sort(v.begin(), v.end());  // \u76F4\u63A5\u6309\u8282\u70B9\u7684\
    \u503C\u7684\u5927\u5C0F\u6392\u4E0B\u5E8F\n  for (int i = 0; i < v.size(); i++)\
    \  // \u7136\u540E\u6328\u4E2A\u4E22\u51FA\u6765\uFF0C\u76F4\u5230\u4E22\u51FA\
    k\u4E2A\u5143\u7D20\u4E3A\u6B62\n  {\n    k -= v[i].second;\n    if (k <= 0) return\
    \ v[i].first;\n  }\n}\n"
  code: "#include <algorithm>\n#include <set>\n#include <vector>\n\nstruct ChthollyNode\
    \ {\n  int l, r;\n  mutable int v;\n  ChthollyNode(int l, int r, int v) : l(l),\
    \ r(r), v(v) {}\n  bool operator<(const ChthollyNode &o) const { return l < o.l;\
    \ }\n};\n\nstd::set<ChthollyNode> tr;\nstd::set<ChthollyNode>::iterator split(int\
    \ pos) {\n  auto it = tr.lower_bound(ChthollyNode(pos, 0, 0));\n  if (it != tr.end()\
    \ && it->l == pos) return it;\n  it--;\n  int l = it->l, r = it->r, v = it->v;\n\
    \  tr.erase(it);\n  tr.insert(ChthollyNode(l, pos - 1, v));\n  return tr.insert(ChthollyNode(pos,\
    \ r, v)).first;\n}\n\n// range add\nvoid add(int l, int r, int v) {  // [l, r]\n\
    \  auto end = split(r + 1);\n  for (auto it = split(l); it != end; it++) it->v\
    \ += v;\n}\n\n// range assign\nvoid assign(int l, int r, int v) {\n  auto end\
    \ = split(r + 1), begin = split(l);  // \u987A\u5E8F\u4E0D\u80FD\u98A0\u5012\uFF0C\
    \u5426\u5219\u53EF\u80FDRE\n  tr.erase(begin, end);                       // \u6E05\
    \u9664\u4E00\u7CFB\u5217\u8282\u70B9\n  tr.insert(ChthollyNode(l, r, v));    \
    \       // \u63D2\u5165\u65B0\u7684\u8282\u70B9\n}\n\n// range kth\nint kth(int\
    \ l, int r, int k) {\n  auto end = split(r + 1);\n  std::vector<std::pair<int,\
    \ int>> v;  // \u8FD9\u4E2Apair\u91CC\u5B58\u8282\u70B9\u7684\u503C\u548C\u533A\
    \u95F4\u957F\u5EA6\n  for (auto it = split(l); it != end; it++)\n    v.emplace_back(it->v,\
    \ it->r - it->l + 1);\n  std::sort(v.begin(), v.end());  // \u76F4\u63A5\u6309\
    \u8282\u70B9\u7684\u503C\u7684\u5927\u5C0F\u6392\u4E0B\u5E8F\n  for (int i = 0;\
    \ i < v.size(); i++)  // \u7136\u540E\u6328\u4E2A\u4E22\u51FA\u6765\uFF0C\u76F4\
    \u5230\u4E22\u51FAk\u4E2A\u5143\u7D20\u4E3A\u6B62\n  {\n    k -= v[i].second;\n\
    \    if (k <= 0) return v[i].first;\n  }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/chtholly_tree.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/chtholly_tree.hpp
layout: document
redirect_from:
- /library/data_structure/chtholly_tree.hpp
- /library/data_structure/chtholly_tree.hpp.html
title: data_structure/chtholly_tree.hpp
---
