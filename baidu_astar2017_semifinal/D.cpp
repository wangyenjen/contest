/// Author: Wang, Yen-Jen
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Point {
  ll x, y;

  Point(ll _x = 0, ll _y = 0) : x(_x), y(_y) {}

  bool operator < (const Point &rhs) const {
    if (x != rhs.x) return x < rhs.x;
    else return y < rhs.y;
  }
};

typedef Point Vector;

const Vector DV[4] = {Vector(1, 0), Vector(0, -1), Vector(-1, 0), Vector(0, 1)};

inline Point operator + (Point p, Vector v) {
  return Point(p.x + v.x, p.y + v.y);
}

inline Vector operator - (Point a, Point b) {
  return Vector(a.x - b.x, a.y - b.y);
}

inline Vector operator * (Vector v, ll p) {
  return Vector(v.x * p, v.y * p);
}

inline ll cross(Vector a, Vector b) {
  return a.x * b.y - a.y * b.x;
}

inline ll dot(Vector a, Vector b) {
  return a.x * b.x + a.y * b.y;
}

inline int sign(ll x) {
  if (x < 0)
    return -1;
  else if (x > 0)
    return 1;
  else
    return 0;
}

inline bool banana(Point a, Point b, Point c, Point d) {
  if (b < a) swap(a, b);
  if (d < c) swap(c, d);
  if (b.x < c.x) return 0;
  if (d.x < a.x) return 0;
  if (b.y < c.y) return 0;
  if (d.y < a.y) return 0;
  return 1;
  /*
  if (cross(d - a, c - a) == 0 && cross(d - b, c - b) == 0)
    return dot(c - a, d - a) <= 0 || dot(c - b, d - b) <= 0;
  else
    return sign(cross(b - a, c - a)) * sign(cross(b - a, d - a)) <= 0 && sign(cross(d - c, a - c)) * sign(cross(d - c, b - c)) <= 0;
  */
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int N;
    scanf("%d", &N);
    Point p;
    vector<pair<Point, Point> > segs;
    int ans = -1;
    for (int i = 0; i < N; i++) {
      int l;
      scanf("%d", &l);
      Point p2 = p + DV[i % 4] * l;
      segs.push_back(make_pair(p, p2));
      p = p2;
      if (ans == -1) {
        for (int j = max(0, i - 6); j <= i - 2; j++) {
          if (banana(segs[i].first, segs[i].second, segs[j].first, segs[j].second)) {
            ans = i;
            break;
          }
        }
      }
    }
    if (ans != -1) printf("%d\n", ans + 1);
    else puts("Catch you");
  }
  return 0;
}
