#pragma

template <typename T>
struct Dijkstra_Dense_Graph {
  const T INF = std::numeric_limits<T>::max() / 2;
  int n;
  std::vector<std::vector<T>> g;
  std::vector<bool> vis;
  Dijkstra_Dense_Graph(int _n) : n(_n), g(_n, std::vector<T>(_n, INF)) {}

  void add_edge(int u, int v, T weight) { g[u][v] = std::min(g[u][v], weight); }
  // return dist [0..n - 1] pred[0..n - 1]
  std::pair<std::vector<T>, std::vector<int>> shortest_paths(int s) {
    std::vector<T> dist(n, INF);
    std::vector<bool> vis(n, false);
    std::vector<int> pre(n, -1);
    dist[s] = 0;

    for (int i = 0; i < n; i++) {
      int cur = -1;
      for (int j = 0; j < n; j++) {
        if (!vis[j] && (cur == -1 || dist[cur] > dist[j])) {
          cur = j;
        }
      }
      vis[cur] = true;
      for (int j = 0; j < n; j++) {
        if (dist[j] > dist[cur] + g[cur][j]) {
          dist[j] = dist[cur] + g[cur][j];
          pre[j] = cur;
        }
      }
    }

    return {dist, pre};
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