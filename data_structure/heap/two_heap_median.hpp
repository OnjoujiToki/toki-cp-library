template <typename T>
struct MedianHeaps {
 public:
  std::priority_queue<T> maxHeap;
  std::priority_queue<T, vector<T>, std::greater<T>> minHeap;
  long long min_sum;
  long long max_sum;
  MedianHeaps(){min_sum = 0, max_sum = 0;};
  void addNum(int num) {
    if (maxHeap.size() == minHeap.size()) {
      if (maxHeap.empty() || num <= minHeap.top()) {
        maxHeap.push(num);
        max_sum += num;
      }
      else {
        maxHeap.push(minHeap.top());
        max_sum += minHeap.top();
        
        minHeap.push(num);
        min_sum -= minHeap.top();
        minHeap.pop();
        min_sum += num;
      }
    } else {
      if (num >= maxHeap.top()) {
        minHeap.push(num);
        min_sum += num;
      } else {
        minHeap.push(maxHeap.top());
        min_sum += maxHeap.top();
        max_sum -= maxHeap.top();
        max_sum += num;
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

  T findLeftMedian() {
      if (minHeap.size() == maxHeap.size()) return minHeap.top();
      return maxHeap.top();   
  }
};

