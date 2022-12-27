// credit: emthrm.github.io/library
#include <cstdint>
template <int B = 32, typename T = std::uint32_t>
struct BinaryTrie {
  struct Node {
    Node* nxt[2];
    int child;
    Node() : nxt{nullptr, nullptr}, child(0) {}
  };

  Node* root;

  BinaryTrie() : root(nullptr) {}

  void clear() { root = nullptr; }

  bool empty() const { return !root; }

  int size() const { return root ? root->child : 0; }

  void erase(const T& x) {
    if (root) erase(&root, x, B - 1);
  }

  Node* find(const T& x) const {
    if (!root) return nullptr;
    Node* node = root;
    for (int b = B - 1; b >= 0; --b) {
      const bool digit = x >> b & 1;
      if (!node->nxt[digit]) return nullptr;
      node = node->nxt[digit];
    }
    return node;
  }

  std::pair<Node*, T> operator[](const int n) const { return find_nth(n, 0); }
  // 0 based, find nth xor sum with x
  std::pair<Node*, T> find_nth(int n, const T& x) const {
    assert(0 <= n && n < size());
    Node* node = root;
    T res = 0;
    for (int b = B - 1; b >= 0; --b) {
      bool digit = x >> b & 1;
      const int l_child = (node->nxt[digit] ? node->nxt[digit]->child : 0);
      if (n >= l_child) {
        n -= l_child;
        digit = !digit;
      }
      node = node->nxt[digit];
      if (digit) res |= static_cast<T>(1) << b;
    }
    return {node, res};
  }

  Node* insert(const T& x) {
    if (!root) root = new Node();
    Node* node = root;
    ++node->child;
    for (int b = B - 1; b >= 0; --b) {
      const bool digit = x >> b & 1;
      if (!node->nxt[digit]) node->nxt[digit] = new Node();
      node = node->nxt[digit];
      ++node->child;
    }
    return node;
  }

  int less_than(const T& x) const {
    int res = 0;
    Node* node = root;
    for (int b = B - 1; node && b >= 0; --b) {
      const bool digit = x >> b & 1;
      if (digit && node->nxt[0]) res += node->nxt[0]->child;
      node = node->nxt[digit];
    }
    return res;
  }

  int count(const T& l, const T& r) const {
    return less_than(r) - less_than(l);
  }

  int count(const T& x) const {
    const Node* ptr = find(x);
    return ptr ? ptr->child : 0;
  }

  std::pair<Node*, T> lower_bound(const T& x) const {
    const int lt = less_than(x);
    return lt == size() ? std::make_pair(nullptr, -1) : find_nth(lt, 0);
  }

  std::pair<Node*, T> upper_bound(const T& x) const {
    return lower_bound(x + 1);
  }

  std::pair<Node*, T> max_element(const T& x = 0) const {
    return min_element(~x);
  }

  std::pair<Node*, T> min_element(const T& x = 0) const {
    assert(root);
    Node* node = root;
    T res = 0;
    for (int b = B - 1; b >= 0; --b) {
      bool digit = x >> b & 1;
      if (!node->nxt[digit]) digit = !digit;
      node = node->nxt[digit];
      if (digit) res |= static_cast<T>(1) << b;
    }
    return {node, res};
  }

 private:
  void erase(Node* node, const T& x, int b) {
    if (b == -1) {
      if (--(*node)->child == 0) node = nullptr;
      return;
    }
    const bool digit = x >> b & 1;
    if (!(*node)->nxt[digit]) return;
    (*node)->child -= (*node)->nxt[digit]->child;
    erase(&(*node)->nxt[digit], x, b - 1);
    if ((*node)->nxt[digit]) {
      (*node)->child += (*node)->nxt[digit]->child;
    } else if ((*node)->child == 0) {
      node = nullptr;
    }
  }
};