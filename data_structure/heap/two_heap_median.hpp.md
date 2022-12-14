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
  bundledCode: "#line 1 \"data_structure/heap/two_heap_median.hpp\"\ntemplate <typename\
    \ T>\nstruct MedianHeaps {\n public:\n  std::priority_queue<T> maxHeap;\n  std::priority_queue<T,\
    \ vector<T>, std::greater<T>> minHeap;\n  long long min_sum;\n  long long max_sum;\n\
    \  MedianHeaps(){min_sum = 0, max_sum = 0;};\n  void addNum(int num) {\n    if\
    \ (maxHeap.size() == minHeap.size()) {\n      if (maxHeap.empty() || num <= minHeap.top())\
    \ {\n        maxHeap.push(num);\n        max_sum += num;\n      }\n      else\
    \ {\n        maxHeap.push(minHeap.top());\n        max_sum += minHeap.top();\n\
    \        \n        minHeap.push(num);\n        min_sum -= minHeap.top();\n   \
    \     minHeap.pop();\n        min_sum += num;\n      }\n    } else {\n      if\
    \ (num >= maxHeap.top()) {\n        minHeap.push(num);\n        min_sum += num;\n\
    \      } else {\n        minHeap.push(maxHeap.top());\n        min_sum += maxHeap.top();\n\
    \        max_sum -= maxHeap.top();\n        max_sum += num;\n        maxHeap.pop();\n\
    \        maxHeap.push(num);\n      }\n    }\n    assert(abs((int)maxHeap.size()\
    \ - (int)minHeap.size()) <= 1);\n  }\n\n  double findMedian() {\n    if (maxHeap.size()\
    \ == minHeap.size()) {\n      return double(maxHeap.top() + minHeap.top()) / 2.0;\n\
    \    } else\n      return maxHeap.top();\n  }\n\n  T findLeftMedian() {\n    \
    \  if (minHeap.size() == maxHeap.size()) return minHeap.top();\n      return maxHeap.top();\
    \   \n  }\n};\n\n"
  code: "template <typename T>\nstruct MedianHeaps {\n public:\n  std::priority_queue<T>\
    \ maxHeap;\n  std::priority_queue<T, vector<T>, std::greater<T>> minHeap;\n  long\
    \ long min_sum;\n  long long max_sum;\n  MedianHeaps(){min_sum = 0, max_sum =\
    \ 0;};\n  void addNum(int num) {\n    if (maxHeap.size() == minHeap.size()) {\n\
    \      if (maxHeap.empty() || num <= minHeap.top()) {\n        maxHeap.push(num);\n\
    \        max_sum += num;\n      }\n      else {\n        maxHeap.push(minHeap.top());\n\
    \        max_sum += minHeap.top();\n        \n        minHeap.push(num);\n   \
    \     min_sum -= minHeap.top();\n        minHeap.pop();\n        min_sum += num;\n\
    \      }\n    } else {\n      if (num >= maxHeap.top()) {\n        minHeap.push(num);\n\
    \        min_sum += num;\n      } else {\n        minHeap.push(maxHeap.top());\n\
    \        min_sum += maxHeap.top();\n        max_sum -= maxHeap.top();\n      \
    \  max_sum += num;\n        maxHeap.pop();\n        maxHeap.push(num);\n     \
    \ }\n    }\n    assert(abs((int)maxHeap.size() - (int)minHeap.size()) <= 1);\n\
    \  }\n\n  double findMedian() {\n    if (maxHeap.size() == minHeap.size()) {\n\
    \      return double(maxHeap.top() + minHeap.top()) / 2.0;\n    } else\n     \
    \ return maxHeap.top();\n  }\n\n  T findLeftMedian() {\n      if (minHeap.size()\
    \ == maxHeap.size()) return minHeap.top();\n      return maxHeap.top();   \n \
    \ }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/heap/two_heap_median.hpp
  requiredBy: []
  timestamp: '2022-12-14 00:58:17-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/heap/two_heap_median.hpp
layout: document
redirect_from:
- /library/data_structure/heap/two_heap_median.hpp
- /library/data_structure/heap/two_heap_median.hpp.html
title: data_structure/heap/two_heap_median.hpp
---
