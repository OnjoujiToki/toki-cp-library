#pragma once

template <typename T>
struct Dijkstra {
  using edge = std::pair<T, int>;  // weight & vertex id num
  const T INF = std::numeric_limits<T>::max() / 2;
  int n;
  std::vector<std::vector<edge>> edges;
  Dijkstra(int _n) : n(_n), edges(n) {}

  // Add a directed edge from u -> v;
  void add_edge(int u, int v, T weight) { edges[u].emplace_back(weight, v); }
  // return dist [0..n - 1] pred[0..n - 1]
  std::pair<std::vector<T>, std::vector<int>> shortest_paths(int s) {
    std::vector<T> dist(n, INF);
    std::vector<int> pred(n, -1);
    dist[s] = 0;
    std::priority_queue<edge, std::vector<edge>, std::greater<edge>> pq;
    pq.emplace(0, s);

    while (!pq.empty()) {
      auto [d, u] = pq.top();
      pq.pop();
      if (d == dist[u]) {
        for (auto [w, v] : edges[u]) {
          if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            pred[v] = u;
            pq.emplace(dist[v], v);
          }
        }
      }
    }
    return {dist, pred};
  }

  std::vector<int> get_path(int v, const std::vector<int>& pred) {
    std::vector<int> path = {v};
    while (pred[v] != -1) {
      path.push_back(pred[v]);
      v = pred[v];
    }

    reverse(path.begin(), path.end());
    return path;
  }
};
