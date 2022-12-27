struct Circle {
  int x, y, r;

  Circle(int x, int y, int r) : x(x), y(y), r(r) {}
  Circle() : Circle(0, 0, 0) {}  // 调用有参数的构造函数
};

bool intersect(const Circle& c1, const Circle& c2) {
  if (c1.x == c2.x and c1.y == c2.y) {
    return c1.r == c2.r;
  }
  long long d =
      1LL * (c1.x - c2.x) * (c1.x - c2.x) + 1LL * (c1.y - c2.y) * (c1.y - c2.y);
  return d <= 1LL * (c1.r + c2.r) * (c1.r + c2.r);
}

bool on_circle(const Circle& c, int x_p, int y_p) {
  long long d =
      1LL * (x_p - c.x) * (x_p - c.x) + 1LL * (y_p - c.y) * (y_p - c.y);
  return d == 1LL * c.r * c.r;
}