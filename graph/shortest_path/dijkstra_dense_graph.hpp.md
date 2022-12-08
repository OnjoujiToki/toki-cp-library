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
  bundledCode: "#line 1 \"graph/shortest_path/dijkstra_dense_graph.hpp\"\n#pragma\n\
    \ntemplate <typename T>\nstruct Dijkstra_Dense_Graph {\n  const T INF = std::numeric_limits<T>::max()\
    \ / 2;\n  int n;\n  std::vector<std::vector<T>> g;\n  std::vector<bool> vis;\n\
    \  Dijkstra_Dense_Graph(int _n) : n(_n), g(_n, std::vector<T>(_n, INF)) {}\n\n\
    \  void add_edge(int u, int v, T weight) { g[u][v] = std::min(g[u][v], weight);\
    \ }\n  // return dist [0..n - 1] pred[0..n - 1]\n  std::pair<std::vector<T>, std::vector<int>>\
    \ shortest_paths(int s) {\n    std::vector<T> dist(n, INF);\n    std::vector<bool>\
    \ vis(n, false);\n    std::vector<int> pre(n, -1);\n    dist[s] = 0;\n\n    for\
    \ (int i = 0; i < n; i++) {\n      int cur = -1;\n      for (int j = 0; j < n;\
    \ j++) {\n        if (!vis[j] && (cur == -1 || dist[cur] > dist[j])) {\n     \
    \     cur = j;\n        }\n      }\n      vis[cur] = true;\n      for (int j =\
    \ 0; j < n; j++) {\n        if (dist[j] > dist[cur] + g[cur][j]) {\n         \
    \ dist[j] = dist[cur] + g[cur][j];\n          pre[j] = cur;\n        }\n     \
    \ }\n    }\n\n    return {dist, pre};\n  }\n\n  std::vector<int> get_path(int\
    \ v, const std::vector<int>& pred) {\n    std::vector<int> path = {v};\n    while\
    \ (pred[v] != -1) {\n      path.push_back(pred[v]);\n      v = pred[v];\n    }\n\
    \    reverse(path.begin(), path.end());\n    return path;\n  }\n};\n"
  code: "#pragma\n\ntemplate <typename T>\nstruct Dijkstra_Dense_Graph {\n  const\
    \ T INF = std::numeric_limits<T>::max() / 2;\n  int n;\n  std::vector<std::vector<T>>\
    \ g;\n  std::vector<bool> vis;\n  Dijkstra_Dense_Graph(int _n) : n(_n), g(_n,\
    \ std::vector<T>(_n, INF)) {}\n\n  void add_edge(int u, int v, T weight) { g[u][v]\
    \ = std::min(g[u][v], weight); }\n  // return dist [0..n - 1] pred[0..n - 1]\n\
    \  std::pair<std::vector<T>, std::vector<int>> shortest_paths(int s) {\n    std::vector<T>\
    \ dist(n, INF);\n    std::vector<bool> vis(n, false);\n    std::vector<int> pre(n,\
    \ -1);\n    dist[s] = 0;\n\n    for (int i = 0; i < n; i++) {\n      int cur =\
    \ -1;\n      for (int j = 0; j < n; j++) {\n        if (!vis[j] && (cur == -1\
    \ || dist[cur] > dist[j])) {\n          cur = j;\n        }\n      }\n      vis[cur]\
    \ = true;\n      for (int j = 0; j < n; j++) {\n        if (dist[j] > dist[cur]\
    \ + g[cur][j]) {\n          dist[j] = dist[cur] + g[cur][j];\n          pre[j]\
    \ = cur;\n        }\n      }\n    }\n\n    return {dist, pre};\n  }\n\n  std::vector<int>\
    \ get_path(int v, const std::vector<int>& pred) {\n    std::vector<int> path =\
    \ {v};\n    while (pred[v] != -1) {\n      path.push_back(pred[v]);\n      v =\
    \ pred[v];\n    }\n    reverse(path.begin(), path.end());\n    return path;\n\
    \  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_path/dijkstra_dense_graph.hpp
  requiredBy: []
  timestamp: '2022-12-07 20:20:10-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/shortest_path/dijkstra_dense_graph.hpp
layout: document
redirect_from:
- /library/graph/shortest_path/dijkstra_dense_graph.hpp
- /library/graph/shortest_path/dijkstra_dense_graph.hpp.html
title: graph/shortest_path/dijkstra_dense_graph.hpp
---
