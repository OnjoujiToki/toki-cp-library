#include <algorithm>
#include <set>
#include <vector>

struct ChthollyNode {
  int l, r;
  mutable int v;
  ChthollyNode(int l, int r, int v) : l(l), r(r), v(v) {}
  bool operator<(const ChthollyNode &o) const { return l < o.l; }
};

std::set<ChthollyNode> tr;
std::set<ChthollyNode>::iterator split(int pos) {
  auto it = tr.lower_bound(ChthollyNode(pos, 0, 0));
  if (it != tr.end() && it->l == pos) return it;
  it--;
  int l = it->l, r = it->r, v = it->v;
  tr.erase(it);
  tr.insert(ChthollyNode(l, pos - 1, v));
  return tr.insert(ChthollyNode(pos, r, v)).first;
}

// range add
void add(int l, int r, int v) {  // [l, r]
  auto end = split(r + 1);
  for (auto it = split(l); it != end; it++) it->v += v;
}

// range assign
void assign(int l, int r, int v) {
  auto end = split(r + 1), begin = split(l);  // 顺序不能颠倒，否则可能RE
  tr.erase(begin, end);                       // 清除一系列节点
  tr.insert(ChthollyNode(l, r, v));           // 插入新的节点
}

// range kth
int kth(int l, int r, int k) {
  auto end = split(r + 1);
  std::vector<std::pair<int, int>> v;  // 这个pair里存节点的值和区间长度
  for (auto it = split(l); it != end; it++)
    v.emplace_back(it->v, it->r - it->l + 1);
  std::sort(v.begin(), v.end());  // 直接按节点的值的大小排下序
  for (int i = 0; i < v.size(); i++)  // 然后挨个丢出来，直到丢出k个元素为止
  {
    k -= v[i].second;
    if (k <= 0) return v[i].first;
  }
}
