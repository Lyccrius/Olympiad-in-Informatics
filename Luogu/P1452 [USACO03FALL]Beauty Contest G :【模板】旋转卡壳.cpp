#include <iostream>
#include <algorithm>
#include <deque>

typedef double dbl;

const int maxN = 50000;

int n;
int ans;

struct Point {
    int x, y;

    Point operator-(Point other) const {
        return (Point) {x - other.x, y - other.y};
    }

    int cross(Point other) {
        return x * other.y - y * other.x;
    }

    int vert() {
        return x * x + y * y;
    }
} p[maxN + 10];

bool cmp1(Point a, Point b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

bool cmp2(Point a, Point b) {
    if ((a - p[1]).cross(b - p[1]) != 0) return (a - p[1]).cross(b - p[1]) > 0;
    return a.vert() > b.vert();
}

std::deque<Point> Graham() {
    std::deque<Point> q;
    std::sort(p + 1, p + n + 1, cmp1);
    std::sort(p + 2, p + n + 1, cmp2);
    p[n + 1] = p[1];
    for (int i = 1; i <= n + 1; i++) {
        while (q.size() >= 2 && (q[q.size() - 1] - q[q.size() - 2]).cross(p[i] - q.back()) < 0) q.pop_back();
        q.push_back(p[i]);
    }
    return q;
}

dbl disPointLine(Point p, Point a, Point b) {
    return std::abs(1.0 * (p - a).cross(a - b) / (a - b).vert());
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i].x >> p[i].y;
    std::deque<Point> ch = Graham();
    std::deque<Point> q = ch;
    for (int i = 1; i < ch.size(); i++) q.push_back(ch[i]);
    for (int i = 1, j = 1; i < q.size(); i++) {
        while (j + 1 < q.size() && disPointLine(q[j + 1], q[i], q[i - 1]) >= disPointLine(q[j], q[i], q[i - 1])) j++;
        ans = std::max(ans, (q[j] - q[i]).vert());
        ans = std::max(ans, (q[j] - q[i - 1]).vert());
    } 
    std::cout << ans << '\n';
    return 0;
}