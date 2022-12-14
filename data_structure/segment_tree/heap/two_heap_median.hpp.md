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
  bundledCode: "#line 1 \"data_structure/segment_tree/heap/two_heap_median.hpp\"\n\
    template <typename T>\nstruct MedianHeaps {\n public:\n  std::priority_queue<T>\
    \ maxHeap;\n  std::priority_queue<T, vector<T>, std::greater<T>> minHeap;\n  MedianHeaps(){};\n\
    \  void addNum(int num) {\n    if (maxHeap.size() == minHeap.size()) {\n     \
    \ if (minHeap.empty() || num <= minHeap.top())\n        maxHeap.push(num);\n \
    \     else {\n        maxHeap.push(minHeap.top());\n        minHeap.pop();\n \
    \       minHeap.push(num);\n      }\n    } else {\n      if (num >= maxHeap.top())\
    \ {\n        minHeap.push(num);\n      } else {\n        minHeap.push(maxHeap.top());\n\
    \        maxHeap.pop();\n        maxHeap.push(num);\n      }\n    }\n    assert(abs((int)maxHeap.size()\
    \ - (int)minHeap.size()) <= 1);\n  }\n\n  double findMedian() {\n    if (maxHeap.size()\
    \ == minHeap.size()) {\n      return double(maxHeap.top() + minHeap.top()) / 2.0;\n\
    \    } else\n      return maxHeap.top();\n  }\n\n  T findLeftMedian() { return\
    \ max_Heap.top(); }\n};\n"
  code: "template <typename T>\nstruct MedianHeaps {\n public:\n  std::priority_queue<T>\
    \ maxHeap;\n  std::priority_queue<T, vector<T>, std::greater<T>> minHeap;\n  MedianHeaps(){};\n\
    \  void addNum(int num) {\n    if (maxHeap.size() == minHeap.size()) {\n     \
    \ if (minHeap.empty() || num <= minHeap.top())\n        maxHeap.push(num);\n \
    \     else {\n        maxHeap.push(minHeap.top());\n        minHeap.pop();\n \
    \       minHeap.push(num);\n      }\n    } else {\n      if (num >= maxHeap.top())\
    \ {\n        minHeap.push(num);\n      } else {\n        minHeap.push(maxHeap.top());\n\
    \        maxHeap.pop();\n        maxHeap.push(num);\n      }\n    }\n    assert(abs((int)maxHeap.size()\
    \ - (int)minHeap.size()) <= 1);\n  }\n\n  double findMedian() {\n    if (maxHeap.size()\
    \ == minHeap.size()) {\n      return double(maxHeap.top() + minHeap.top()) / 2.0;\n\
    \    } else\n      return maxHeap.top();\n  }\n\n  T findLeftMedian() { return\
    \ max_Heap.top(); }\n};"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree/heap/two_heap_median.hpp
  requiredBy: []
  timestamp: '2022-12-13 23:45:22-05:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segment_tree/heap/two_heap_median.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree/heap/two_heap_median.hpp
- /library/data_structure/segment_tree/heap/two_heap_median.hpp.html
title: data_structure/segment_tree/heap/two_heap_median.hpp
---
