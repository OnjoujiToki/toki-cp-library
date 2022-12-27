std::vector<int> get_divisors(int x) {
  std::vector<int> res;
  for (int i = 1; i <= x / i; i++)
    if (x % i == 0) {
      res.push_back(i);
      if (i != x / i) res.push_back(x / i);
    }
  std::sort(res.begin(), res.end());
  return res;
}