#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <cmath>

typedef double dbl;

const int maxN = 1e5;
const dbl eps = 1e-6;

int n;
dbl x, y;

struct Point {
    dbl x;
    dbl y;

    dbl rate() {
        return x / y;
    }

    dbl vert() {
        return sqrt(x * x + y * y);
    }

    dbl cross(Point other) {
        return x * other.y - other.x * y;
    }

    Point operator-(Point other) {
        return (Point) {x - other.x, y - other.y};
    }
} p[maxN + 10];

bool cmp1(Point a, Point b) {
    if (std::abs(a.x - b.x) >= eps) return a.x < b.x;
    return a.y < b.y;
}

bool cmp2(Point a, Point b) {
    if (std::abs((a - p[1]).cross(b - p[1])) >= eps) return (a - p[1]).cross(b - p[1]) > 0;
    return (a - p[1]).vert() > (b - p[1]).vert();
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> x >> y;
        p[i].x = x;
        p[i].y = y;
    }
    std::sort(p + 1, p + n + 1, cmp1);
    std::sort(p + 2, p + n + 1, cmp2);
    p[n + 1] = p[1];
    std::deque<Point> q;
    dbl ans = 0;
    for (int i = 1; i <= n + 1; i++) {
        //printf("%lf, %lf\n", p[i].x, p[i].y);
        while (q.size() >= 2 && (q[q.size() - 1] - q[q.size() - 2]).cross(p[i] - q.back()) < 0) q.pop_back();
        q.push_back(p[i]);
    }
    //printf("\n");
    for (int i = 1; i < q.size(); i++) {
        //printf("%lf, %lf\n", q[i].x, q[i].y);
        ans += (q[i] - q[i - 1]).vert();
    }
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(2) << ans << '\n';
    return 0;
}