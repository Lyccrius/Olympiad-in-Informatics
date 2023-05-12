#include <iostream>

typedef long long lxl;

const int maxN = 1e5;
const lxl inf = 8e18;

int n;

struct Point {
    lxl x, y;

    Point operator-(Point other) const {
        return (Point) {x - other.x, y - other. y};
    }

    lxl cross(Point other) {
        return x * other.y - y * other.x;
    }
} p[2 * maxN + 10];

lxl a;
lxl b;

lxl AreaTriangle(Point a, Point b, Point c) {
    return std::abs((b - a).cross(c - a));
}

lxl ans = inf;

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i].x >> p[i].y;
    for (int i = 1; i <= n; i++) p[n + i] = p[i];
    for (int i = 3; i <= n; i++) a += AreaTriangle(p[1], p[i - 1], p[i]);
    for (int i = 1, j = 2; i <= n; i++) {
        while (4 * b < a) {
            b += AreaTriangle(p[i], p[j], p[j + 1]);
            ans = std::min(ans, std::abs(4 * b - a));
            j++;
        };
        b -= AreaTriangle(p[j], p[i], p[i + 1]);
        ans = std::min(ans, std::abs(4 * b - a));
    }
    std::cout << ans << '\n';
    return 0;
}