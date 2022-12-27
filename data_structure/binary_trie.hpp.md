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
  bundledCode: "#line 1 \"data_structure/binary_trie.hpp\"\n// credit: emthrm.github.io/library\n\
    #include <cstdint>\ntemplate <int B = 32, typename T = std::uint32_t>\nstruct\
    \ BinaryTrie {\n  struct Node {\n    Node* nxt[2];\n    int child;\n    Node()\
    \ : nxt{nullptr, nullptr}, child(0) {}\n  };\n\n  Node* root;\n\n  BinaryTrie()\
    \ : root(nullptr) {}\n\n  void clear() { root = nullptr; }\n\n  bool empty() const\
    \ { return !root; }\n\n  int size() const { return root ? root->child : 0; }\n\
    \n  void erase(const T& x) {\n    if (root) erase(&root, x, B - 1);\n  }\n\n \
    \ Node* find(const T& x) const {\n    if (!root) return nullptr;\n    Node* node\
    \ = root;\n    for (int b = B - 1; b >= 0; --b) {\n      const bool digit = x\
    \ >> b & 1;\n      if (!node->nxt[digit]) return nullptr;\n      node = node->nxt[digit];\n\
    \    }\n    return node;\n  }\n\n  std::pair<Node*, T> operator[](const int n)\
    \ const { return find_nth(n, 0); }\n  // 0 based, find nth xor sum with x\n  std::pair<Node*,\
    \ T> find_nth(int n, const T& x) const {\n    assert(0 <= n && n < size());\n\
    \    Node* node = root;\n    T res = 0;\n    for (int b = B - 1; b >= 0; --b)\
    \ {\n      bool digit = x >> b & 1;\n      const int l_child = (node->nxt[digit]\
    \ ? node->nxt[digit]->child : 0);\n      if (n >= l_child) {\n        n -= l_child;\n\
    \        digit = !digit;\n      }\n      node = node->nxt[digit];\n      if (digit)\
    \ res |= static_cast<T>(1) << b;\n    }\n    return {node, res};\n  }\n\n  Node*\
    \ insert(const T& x) {\n    if (!root) root = new Node();\n    Node* node = root;\n\
    \    ++node->child;\n    for (int b = B - 1; b >= 0; --b) {\n      const bool\
    \ digit = x >> b & 1;\n      if (!node->nxt[digit]) node->nxt[digit] = new Node();\n\
    \      node = node->nxt[digit];\n      ++node->child;\n    }\n    return node;\n\
    \  }\n\n  int less_than(const T& x) const {\n    int res = 0;\n    Node* node\
    \ = root;\n    for (int b = B - 1; node && b >= 0; --b) {\n      const bool digit\
    \ = x >> b & 1;\n      if (digit && node->nxt[0]) res += node->nxt[0]->child;\n\
    \      node = node->nxt[digit];\n    }\n    return res;\n  }\n\n  int count(const\
    \ T& l, const T& r) const {\n    return less_than(r) - less_than(l);\n  }\n\n\
    \  int count(const T& x) const {\n    const Node* ptr = find(x);\n    return ptr\
    \ ? ptr->child : 0;\n  }\n\n  std::pair<Node*, T> lower_bound(const T& x) const\
    \ {\n    const int lt = less_than(x);\n    return lt == size() ? std::make_pair(nullptr,\
    \ -1) : find_nth(lt, 0);\n  }\n\n  std::pair<Node*, T> upper_bound(const T& x)\
    \ const {\n    return lower_bound(x + 1);\n  }\n\n  std::pair<Node*, T> max_element(const\
    \ T& x = 0) const {\n    return min_element(~x);\n  }\n\n  std::pair<Node*, T>\
    \ min_element(const T& x = 0) const {\n    assert(root);\n    Node* node = root;\n\
    \    T res = 0;\n    for (int b = B - 1; b >= 0; --b) {\n      bool digit = x\
    \ >> b & 1;\n      if (!node->nxt[digit]) digit = !digit;\n      node = node->nxt[digit];\n\
    \      if (digit) res |= static_cast<T>(1) << b;\n    }\n    return {node, res};\n\
    \  }\n\n private:\n  void erase(Node* node, const T& x, int b) {\n    if (b ==\
    \ -1) {\n      if (--(*node)->child == 0) node = nullptr;\n      return;\n   \
    \ }\n    const bool digit = x >> b & 1;\n    if (!(*node)->nxt[digit]) return;\n\
    \    (*node)->child -= (*node)->nxt[digit]->child;\n    erase(&(*node)->nxt[digit],\
    \ x, b - 1);\n    if ((*node)->nxt[digit]) {\n      (*node)->child += (*node)->nxt[digit]->child;\n\
    \    } else if ((*node)->child == 0) {\n      node = nullptr;\n    }\n  }\n};\n"
  code: "// credit: emthrm.github.io/library\n#include <cstdint>\ntemplate <int B\
    \ = 32, typename T = std::uint32_t>\nstruct BinaryTrie {\n  struct Node {\n  \
    \  Node* nxt[2];\n    int child;\n    Node() : nxt{nullptr, nullptr}, child(0)\
    \ {}\n  };\n\n  Node* root;\n\n  BinaryTrie() : root(nullptr) {}\n\n  void clear()\
    \ { root = nullptr; }\n\n  bool empty() const { return !root; }\n\n  int size()\
    \ const { return root ? root->child : 0; }\n\n  void erase(const T& x) {\n   \
    \ if (root) erase(&root, x, B - 1);\n  }\n\n  Node* find(const T& x) const {\n\
    \    if (!root) return nullptr;\n    Node* node = root;\n    for (int b = B -\
    \ 1; b >= 0; --b) {\n      const bool digit = x >> b & 1;\n      if (!node->nxt[digit])\
    \ return nullptr;\n      node = node->nxt[digit];\n    }\n    return node;\n \
    \ }\n\n  std::pair<Node*, T> operator[](const int n) const { return find_nth(n,\
    \ 0); }\n  // 0 based, find nth xor sum with x\n  std::pair<Node*, T> find_nth(int\
    \ n, const T& x) const {\n    assert(0 <= n && n < size());\n    Node* node =\
    \ root;\n    T res = 0;\n    for (int b = B - 1; b >= 0; --b) {\n      bool digit\
    \ = x >> b & 1;\n      const int l_child = (node->nxt[digit] ? node->nxt[digit]->child\
    \ : 0);\n      if (n >= l_child) {\n        n -= l_child;\n        digit = !digit;\n\
    \      }\n      node = node->nxt[digit];\n      if (digit) res |= static_cast<T>(1)\
    \ << b;\n    }\n    return {node, res};\n  }\n\n  Node* insert(const T& x) {\n\
    \    if (!root) root = new Node();\n    Node* node = root;\n    ++node->child;\n\
    \    for (int b = B - 1; b >= 0; --b) {\n      const bool digit = x >> b & 1;\n\
    \      if (!node->nxt[digit]) node->nxt[digit] = new Node();\n      node = node->nxt[digit];\n\
    \      ++node->child;\n    }\n    return node;\n  }\n\n  int less_than(const T&\
    \ x) const {\n    int res = 0;\n    Node* node = root;\n    for (int b = B - 1;\
    \ node && b >= 0; --b) {\n      const bool digit = x >> b & 1;\n      if (digit\
    \ && node->nxt[0]) res += node->nxt[0]->child;\n      node = node->nxt[digit];\n\
    \    }\n    return res;\n  }\n\n  int count(const T& l, const T& r) const {\n\
    \    return less_than(r) - less_than(l);\n  }\n\n  int count(const T& x) const\
    \ {\n    const Node* ptr = find(x);\n    return ptr ? ptr->child : 0;\n  }\n\n\
    \  std::pair<Node*, T> lower_bound(const T& x) const {\n    const int lt = less_than(x);\n\
    \    return lt == size() ? std::make_pair(nullptr, -1) : find_nth(lt, 0);\n  }\n\
    \n  std::pair<Node*, T> upper_bound(const T& x) const {\n    return lower_bound(x\
    \ + 1);\n  }\n\n  std::pair<Node*, T> max_element(const T& x = 0) const {\n  \
    \  return min_element(~x);\n  }\n\n  std::pair<Node*, T> min_element(const T&\
    \ x = 0) const {\n    assert(root);\n    Node* node = root;\n    T res = 0;\n\
    \    for (int b = B - 1; b >= 0; --b) {\n      bool digit = x >> b & 1;\n    \
    \  if (!node->nxt[digit]) digit = !digit;\n      node = node->nxt[digit];\n  \
    \    if (digit) res |= static_cast<T>(1) << b;\n    }\n    return {node, res};\n\
    \  }\n\n private:\n  void erase(Node* node, const T& x, int b) {\n    if (b ==\
    \ -1) {\n      if (--(*node)->child == 0) node = nullptr;\n      return;\n   \
    \ }\n    const bool digit = x >> b & 1;\n    if (!(*node)->nxt[digit]) return;\n\
    \    (*node)->child -= (*node)->nxt[digit]->child;\n    erase(&(*node)->nxt[digit],\
    \ x, b - 1);\n    if ((*node)->nxt[digit]) {\n      (*node)->child += (*node)->nxt[digit]->child;\n\
    \    } else if ((*node)->child == 0) {\n      node = nullptr;\n    }\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/binary_trie.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/binary_trie.hpp
layout: document
redirect_from:
- /library/data_structure/binary_trie.hpp
- /library/data_structure/binary_trie.hpp.html
title: data_structure/binary_trie.hpp
---
