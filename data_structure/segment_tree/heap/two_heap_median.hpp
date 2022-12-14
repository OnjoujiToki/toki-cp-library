template <typename T>
struct MedianHeaps {
 public:
  std::priority_queue<T> maxHeap;
  std::priority_queue<T, vector<T>, std::greater<T>> minHeap;
  MedianHeaps(){};
  void addNum(int num) {
    if (maxHeap.size() == minHeap.size()) {
      if (minHeap.empty() || num <= minHeap.top())
        maxHeap.push(num);
      else {
        maxHeap.push(minHeap.top());
        minHeap.pop();
        minHeap.push(num);
      }
    } else {
      if (num >= maxHeap.top()) {
        minHeap.push(num);
      } else {
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        maxHeap.push(num);
      }
    }
    assert(abs((int)maxHeap.size() - (int)minHeap.size()) <= 1);
  }

  double findMedian() {
    if (maxHeap.size() == minHeap.size()) {
      return double(maxHeap.top() + minHeap.top()) / 2.0;
    } else
      return maxHeap.top();
  }

  T findLeftMedian() { return maxHeap.top(); }
};