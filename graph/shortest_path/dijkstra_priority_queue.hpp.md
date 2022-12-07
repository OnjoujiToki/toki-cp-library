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
  bundledCode: "#line 2 \"graph/shortest_path/dijkstra_priority_queue.hpp\"\n\ntemplate\
    \ <typename T>\nstruct Dijkstra {\n  using edge = std::pair<T, int>;  // weight\
    \ & vertex id num\n  const T INF = std::numeric_limits<T>::max() / 2;\n  int n;\n\
    \  std::vector<std::vector<edge>> edges;\n  Dijkstra(int _n) : n(_n), edges(n)\
    \ {}\n\n  // Add a directed edge from u -> v;\n  void add_edge(int u, int v, T\
    \ weight) { edges[u].emplace_back(weight, v); }\n  // return dist [0..n - 1] pred[0..n\
    \ - 1]\n  std::pair<std::vector<T>, std::vector<int>> shortest_paths(int s) {\n\
    \    std::vector<T> dist(n, INF);\n    std::vector<int> pred(n, -1);\n    dist[s]\
    \ = 0;\n    std::priority_queue<edge, std::vector<edge>, std::greater<edge>> pq;\n\
    \    pq.emplace(0, s);\n\n    while (!pq.empty()) {\n      auto [d, u] = pq.top();\n\
    \      pq.pop();\n      if (d == dist[u]) {\n        for (auto [w, v] : edges[u])\
    \ {\n          if (dist[v] > dist[u] + w) {\n            dist[v] = dist[u] + w;\n\
    \            pred[v] = u;\n            pq.emplace(dist[v], v);\n          }\n\
    \        }\n      }\n    }\n    return {dist, pred};\n  }\n\n  std::vector<int>\
    \ get_path(int v, const std::vector<int>& pred) {\n    std::vector<int> path =\
    \ {v};\n    while (pred[v] != -1) {\n      path.push_back(pred[v]);\n      v =\
    \ pred[v];\n    }\n\n    reverse(path.begin(), path.end());\n    return path;\n\
    \  }\n};\n"
  code: "#pragma once\n\ntemplate <typename T>\nstruct Dijkstra {\n  using edge =\
    \ std::pair<T, int>;  // weight & vertex id num\n  const T INF = std::numeric_limits<T>::max()\
    \ / 2;\n  int n;\n  std::vector<std::vector<edge>> edges;\n  Dijkstra(int _n)\
    \ : n(_n), edges(n) {}\n\n  // Add a directed edge from u -> v;\n  void add_edge(int\
    \ u, int v, T weight) { edges[u].emplace_back(weight, v); }\n  // return dist\
    \ [0..n - 1] pred[0..n - 1]\n  std::pair<std::vector<T>, std::vector<int>> shortest_paths(int\
    \ s) {\n    std::vector<T> dist(n, INF);\n    std::vector<int> pred(n, -1);\n\
    \    dist[s] = 0;\n    std::priority_queue<edge, std::vector<edge>, std::greater<edge>>\
    \ pq;\n    pq.emplace(0, s);\n\n    while (!pq.empty()) {\n      auto [d, u] =\
    \ pq.top();\n      pq.pop();\n      if (d == dist[u]) {\n        for (auto [w,\
    \ v] : edges[u]) {\n          if (dist[v] > dist[u] + w) {\n            dist[v]\
    \ = dist[u] + w;\n            pred[v] = u;\n            pq.emplace(dist[v], v);\n\
    \          }\n        }\n      }\n    }\n    return {dist, pred};\n  }\n\n  std::vector<int>\
    \ get_path(int v, const std::vector<int>& pred) {\n    std::vector<int> path =\
    \ {v};\n    while (pred[v] != -1) {\n      path.push_back(pred[v]);\n      v =\
    \ pred[v];\n    }\n\n    reverse(path.begin(), path.end());\n    return path;\n\
    \  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_path/dijkstra_priority_queue.hpp
  requiredBy: []
  timestamp: '2022-12-07 18:00:26-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/shortest_path/dijkstra_priority_queue.hpp
layout: document
title: Dijkstra By Priority Queue
---

## Description
...
