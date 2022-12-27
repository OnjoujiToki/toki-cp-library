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
  bundledCode: "#line 1 \"data_structure/interval_manager.hpp\"\n#include <set>\n\n\
    template <typename T>\nstruct IntervalsManagedBySet {\n  using IntervalsType =\
    \ std::set<std::pair<T, T>>;\n  IntervalsType intervals{\n      {std::numeric_limits<T>::lowest(),\
    \ std::numeric_limits<T>::lowest()},\n      {std::numeric_limits<T>::max(), std::numeric_limits<T>::max()}};\n\
    \n  IntervalsManagedBySet() = default;\n\n  bool contains(const T x) const { return\
    \ contains(x, x); }\n\n  bool contains(const T left, const T right) const {\n\
    \    return find(left, right) != intervals.end();\n  }\n\n  std::pair<typename\
    \ IntervalsType::const_iterator, bool> erase(const T x) {\n    typename IntervalsType::const_iterator\
    \ it = intervals.lower_bound({x, x});\n    if (it->first == x) {\n      const\
    \ T right = it->second;\n      it = intervals.erase(it);\n      if (x + 1 <= right)\
    \ it = intervals.emplace(x + 1, right).first;\n    } else {\n      it = std::prev(it);\n\
    \      T left, right;\n      std::tie(left, right) = *it;\n      if (right < x)\
    \ return {std::next(it), false};\n      intervals.erase(it);\n      it = std::next(intervals.emplace(left,\
    \ x - 1).first);\n      if (x + 1 <= right) it = intervals.emplace(x + 1, right).first;\n\
    \    }\n    return {it, true};\n  }\n\n  std::pair<typename IntervalsType::const_iterator,\
    \ T> erase(const T left,\n                                                   \
    \          const T right) {\n    assert(left <= right);\n    typename IntervalsType::const_iterator\
    \ it =\n        intervals.lower_bound({left, left});\n    T res = 0;\n    for\
    \ (; it->second <= right; it = intervals.erase(it)) {\n      res += it->second\
    \ - it->first + 1;\n    }\n    if (it->first <= right) {\n      res += right -\
    \ it->first + 1;\n      const T r = it->second;\n      intervals.erase(it);\n\
    \      it = intervals.emplace(right + 1, r).first;\n    }\n    if (left <= std::prev(it)->second)\
    \ {\n      it = std::prev(it);\n      T l, r;\n      std::tie(l, r) = *it;\n \
    \     intervals.erase(it);\n      if (right < r) {\n        res += right - left\
    \ + 1;\n        intervals.emplace(right + 1, r);\n      } else {\n        res\
    \ += r - left + 1;\n      }\n      it = std::next(intervals.emplace(l, left -\
    \ 1).first);\n    }\n    return {it, res};\n  }\n\n  typename IntervalsType::const_iterator\
    \ find(const T x) const {\n    return find(x, x);\n  }\n\n  typename IntervalsType::const_iterator\
    \ find(const T left,\n                                              const T right)\
    \ const {\n    typename IntervalsType::const_iterator it =\n        intervals.lower_bound({left,\
    \ left});\n    if (left < it->first) it = std::prev(it);\n    return it->first\
    \ <= left && right <= it->second ? it : intervals.end();\n  }\n\n  std::pair<typename\
    \ IntervalsType::const_iterator, bool> insert(const T x) {\n    typename IntervalsType::const_iterator\
    \ it = intervals.lower_bound({x, x});\n    if (it->first == x) return {it, false};\n\
    \    if (x <= std::prev(it)->second) return {std::prev(it), false};\n    T left\
    \ = x, right = x;\n    if (x + 1 == it->first) {\n      right = it->second;\n\
    \      it = intervals.erase(it);\n    }\n    if (std::prev(it)->second == x -\
    \ 1) {\n      it = std::prev(it);\n      left = it->first;\n      intervals.erase(it);\n\
    \    }\n    return {intervals.emplace(left, right).first, true};\n  }\n\n  std::pair<typename\
    \ IntervalsType::const_iterator, T> insert(T left, T right) {\n    assert(left\
    \ <= right);\n    typename IntervalsType::const_iterator it =\n        intervals.lower_bound({left,\
    \ left});\n    if (left <= std::prev(it)->second) {\n      it = std::prev(it);\n\
    \      left = it->first;\n    }\n    T res = 0;\n    if (left == it->first &&\
    \ right <= it->second) return {it, res};\n    for (; it->second <= right; it =\
    \ intervals.erase(it)) {\n      res -= it->second - it->first + 1;\n    }\n  \
    \  if (it->first <= right) {\n      res -= it->second - it->first + 1;\n     \
    \ right = it->second;\n      it = intervals.erase(it);\n    }\n    res += right\
    \ - left + 1;\n    if (right + 1 == it->first) {\n      right = it->second;\n\
    \      it = intervals.erase(it);\n    }\n    if (std::prev(it)->second == left\
    \ - 1) {\n      it = std::prev(it);\n      left = it->first;\n      intervals.erase(it);\n\
    \    }\n    return {intervals.emplace(left, right).first, res};\n  }\n\n  T mex(const\
    \ T x = 0) const {\n    auto it = intervals.lower_bound({x, x});\n    if (x <=\
    \ std::prev(it)->second) it = std::prev(it);\n    return x < it->first ? x : it->second\
    \ + 1;\n  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n         \
    \                         const IntervalsManagedBySet &x) {\n    if (x.intervals.size()\
    \ == 2) return os;\n    auto it = next(x.intervals.begin());\n    while (true)\
    \ {\n      os << '[' << it->first << \", \" << it->second << ']';\n      it =\
    \ next(it);\n      if (next(it) == x.intervals.end()) break;\n      os << ' ';\n\
    \    }\n    return os;\n  }\n};\n"
  code: "#include <set>\n\ntemplate <typename T>\nstruct IntervalsManagedBySet {\n\
    \  using IntervalsType = std::set<std::pair<T, T>>;\n  IntervalsType intervals{\n\
    \      {std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest()},\n\
    \      {std::numeric_limits<T>::max(), std::numeric_limits<T>::max()}};\n\n  IntervalsManagedBySet()\
    \ = default;\n\n  bool contains(const T x) const { return contains(x, x); }\n\n\
    \  bool contains(const T left, const T right) const {\n    return find(left, right)\
    \ != intervals.end();\n  }\n\n  std::pair<typename IntervalsType::const_iterator,\
    \ bool> erase(const T x) {\n    typename IntervalsType::const_iterator it = intervals.lower_bound({x,\
    \ x});\n    if (it->first == x) {\n      const T right = it->second;\n      it\
    \ = intervals.erase(it);\n      if (x + 1 <= right) it = intervals.emplace(x +\
    \ 1, right).first;\n    } else {\n      it = std::prev(it);\n      T left, right;\n\
    \      std::tie(left, right) = *it;\n      if (right < x) return {std::next(it),\
    \ false};\n      intervals.erase(it);\n      it = std::next(intervals.emplace(left,\
    \ x - 1).first);\n      if (x + 1 <= right) it = intervals.emplace(x + 1, right).first;\n\
    \    }\n    return {it, true};\n  }\n\n  std::pair<typename IntervalsType::const_iterator,\
    \ T> erase(const T left,\n                                                   \
    \          const T right) {\n    assert(left <= right);\n    typename IntervalsType::const_iterator\
    \ it =\n        intervals.lower_bound({left, left});\n    T res = 0;\n    for\
    \ (; it->second <= right; it = intervals.erase(it)) {\n      res += it->second\
    \ - it->first + 1;\n    }\n    if (it->first <= right) {\n      res += right -\
    \ it->first + 1;\n      const T r = it->second;\n      intervals.erase(it);\n\
    \      it = intervals.emplace(right + 1, r).first;\n    }\n    if (left <= std::prev(it)->second)\
    \ {\n      it = std::prev(it);\n      T l, r;\n      std::tie(l, r) = *it;\n \
    \     intervals.erase(it);\n      if (right < r) {\n        res += right - left\
    \ + 1;\n        intervals.emplace(right + 1, r);\n      } else {\n        res\
    \ += r - left + 1;\n      }\n      it = std::next(intervals.emplace(l, left -\
    \ 1).first);\n    }\n    return {it, res};\n  }\n\n  typename IntervalsType::const_iterator\
    \ find(const T x) const {\n    return find(x, x);\n  }\n\n  typename IntervalsType::const_iterator\
    \ find(const T left,\n                                              const T right)\
    \ const {\n    typename IntervalsType::const_iterator it =\n        intervals.lower_bound({left,\
    \ left});\n    if (left < it->first) it = std::prev(it);\n    return it->first\
    \ <= left && right <= it->second ? it : intervals.end();\n  }\n\n  std::pair<typename\
    \ IntervalsType::const_iterator, bool> insert(const T x) {\n    typename IntervalsType::const_iterator\
    \ it = intervals.lower_bound({x, x});\n    if (it->first == x) return {it, false};\n\
    \    if (x <= std::prev(it)->second) return {std::prev(it), false};\n    T left\
    \ = x, right = x;\n    if (x + 1 == it->first) {\n      right = it->second;\n\
    \      it = intervals.erase(it);\n    }\n    if (std::prev(it)->second == x -\
    \ 1) {\n      it = std::prev(it);\n      left = it->first;\n      intervals.erase(it);\n\
    \    }\n    return {intervals.emplace(left, right).first, true};\n  }\n\n  std::pair<typename\
    \ IntervalsType::const_iterator, T> insert(T left, T right) {\n    assert(left\
    \ <= right);\n    typename IntervalsType::const_iterator it =\n        intervals.lower_bound({left,\
    \ left});\n    if (left <= std::prev(it)->second) {\n      it = std::prev(it);\n\
    \      left = it->first;\n    }\n    T res = 0;\n    if (left == it->first &&\
    \ right <= it->second) return {it, res};\n    for (; it->second <= right; it =\
    \ intervals.erase(it)) {\n      res -= it->second - it->first + 1;\n    }\n  \
    \  if (it->first <= right) {\n      res -= it->second - it->first + 1;\n     \
    \ right = it->second;\n      it = intervals.erase(it);\n    }\n    res += right\
    \ - left + 1;\n    if (right + 1 == it->first) {\n      right = it->second;\n\
    \      it = intervals.erase(it);\n    }\n    if (std::prev(it)->second == left\
    \ - 1) {\n      it = std::prev(it);\n      left = it->first;\n      intervals.erase(it);\n\
    \    }\n    return {intervals.emplace(left, right).first, res};\n  }\n\n  T mex(const\
    \ T x = 0) const {\n    auto it = intervals.lower_bound({x, x});\n    if (x <=\
    \ std::prev(it)->second) it = std::prev(it);\n    return x < it->first ? x : it->second\
    \ + 1;\n  }\n\n  friend std::ostream &operator<<(std::ostream &os,\n         \
    \                         const IntervalsManagedBySet &x) {\n    if (x.intervals.size()\
    \ == 2) return os;\n    auto it = next(x.intervals.begin());\n    while (true)\
    \ {\n      os << '[' << it->first << \", \" << it->second << ']';\n      it =\
    \ next(it);\n      if (next(it) == x.intervals.end()) break;\n      os << ' ';\n\
    \    }\n    return os;\n  }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/interval_manager.hpp
  requiredBy: []
  timestamp: '2022-12-27 18:14:54-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/interval_manager.hpp
layout: document
redirect_from:
- /library/data_structure/interval_manager.hpp
- /library/data_structure/interval_manager.hpp.html
title: data_structure/interval_manager.hpp
---
