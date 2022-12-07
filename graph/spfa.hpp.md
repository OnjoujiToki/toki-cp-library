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
  bundledCode: "#line 2 \"graph/spfa.hpp\"\n\ntemplate <typename T>\nstruct Spfa {\n\
    \  using edge = std::pair<T, int>;  // weight & vertex id num\n  const T INF =\
    \ std::numeric_limits<T>::max() / 2;\n  int n;\n  std::vector<std::vector<edge>>\
    \ edges;\n\n  std::vector<bool> inQueue;\n  Spfa(int _n) : n(_n), edges(n) {}\n\
    \n  // Add a directed edge from u -> v;\n  void add_edge(int u, int v, T weight)\
    \ { edges[u].emplace_back(weight, v); }\n\n  // return dist [0..n - 1] pred[0..n\
    \ - 1]\n  std::pair<std::vector<T>, std::vector<int>> shortest_paths(int s) {\n\
    \    std::vector<T> dist(n, INF);\n    std::vector<int> pred(n, -1);\n    std::vector<bool>\
    \ inQueue(n, false);\n    std::queue<int> q;\n    dist[s] = 0;\n    inQueue[s]\
    \ = true;\n    q.emplace(s);\n    while (!q.empty()) {\n      int u = q.front();\n\
    \      q.pop();\n      inQueue[u] = false;\n      for (auto [w, v] : edges[u])\
    \ {\n        if (dist[v] > dist[u] + w) {\n          dist[v] = dist[u] + w;\n\
    \          pred[v] = u;\n          if (!inQueue[v]) {\n            q.emplace(v);\n\
    \            inQueue[v] = true;\n          }\n        }\n      }\n    }\n    return\
    \ {dist, pred};\n  }\n\n  std::vector<int> get_path(int v, const std::vector<int>&\
    \ pred) {\n    std::vector<int> path = {v};\n    while (pred[v] != -1) {\n   \
    \   path.push_back(pred[v]);\n      v = pred[v];\n    }\n\n    reverse(path.begin(),\
    \ path.end());\n    return path;\n  }\n};\n"
  code: "#pragma once\n\ntemplate <typename T>\nstruct Spfa {\n  using edge = std::pair<T,\
    \ int>;  // weight & vertex id num\n  const T INF = std::numeric_limits<T>::max()\
    \ / 2;\n  int n;\n  std::vector<std::vector<edge>> edges;\n\n  std::vector<bool>\
    \ inQueue;\n  Spfa(int _n) : n(_n), edges(n) {}\n\n  // Add a directed edge from\
    \ u -> v;\n  void add_edge(int u, int v, T weight) { edges[u].emplace_back(weight,\
    \ v); }\n\n  // return dist [0..n - 1] pred[0..n - 1]\n  std::pair<std::vector<T>,\
    \ std::vector<int>> shortest_paths(int s) {\n    std::vector<T> dist(n, INF);\n\
    \    std::vector<int> pred(n, -1);\n    std::vector<bool> inQueue(n, false);\n\
    \    std::queue<int> q;\n    dist[s] = 0;\n    inQueue[s] = true;\n    q.emplace(s);\n\
    \    while (!q.empty()) {\n      int u = q.front();\n      q.pop();\n      inQueue[u]\
    \ = false;\n      for (auto [w, v] : edges[u]) {\n        if (dist[v] > dist[u]\
    \ + w) {\n          dist[v] = dist[u] + w;\n          pred[v] = u;\n         \
    \ if (!inQueue[v]) {\n            q.emplace(v);\n            inQueue[v] = true;\n\
    \          }\n        }\n      }\n    }\n    return {dist, pred};\n  }\n\n  std::vector<int>\
    \ get_path(int v, const std::vector<int>& pred) {\n    std::vector<int> path =\
    \ {v};\n    while (pred[v] != -1) {\n      path.push_back(pred[v]);\n      v =\
    \ pred[v];\n    }\n\n    reverse(path.begin(), path.end());\n    return path;\n\
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/spfa.hpp
  requiredBy: []
  timestamp: '2022-12-07 16:45:50-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/spfa.hpp
layout: document
redirect_from:
- /library/graph/spfa.hpp
- /library/graph/spfa.hpp.html
title: graph/spfa.hpp
---
