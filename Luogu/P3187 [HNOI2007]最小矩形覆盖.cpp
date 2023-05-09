#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <cmath>

typedef double dbl;

const int maxN = 50000;
const dbl inf = 1e10;
const dbl eps = 1e-10;

int n;

struct Point {
    dbl x, y;

    Point operator+(Point other) {
        return (Point) {x + other.x, y + other.y};
    }

    Point operator-(Point other) {
        return (Point) {x - other.x, y - other.y};
    }

    Point operator*(dbl k) {
        return (Point) {k * x, k * y};
    }

    dbl dot(Point other) {
        return x * other.x + y * other.y;
    }

    dbl cross(Point other) {
        return x * other.y - y * other.x;
    }

    dbl vert() {
        return sqrt(x * x + y * y);
    }
} p[maxN + 10];

dbl ans = inf;
Point res[5];

bool cmp1(Point a, Point b) {
    if (std::abs(a.x - b.x) >= eps) return a.x < b.x;
    return a.y < b.y;
}

bool cmp2(Point a, Point b) {
    if (std::abs((a - p[1]).cross(b - p[1])) >= eps) return (a - p[1]).cross(b - p[1]) > 0;
    return (a - p[1]).vert() > (b - p[1]).vert();
}

bool cmp3(Point a, Point b) {
    if (std::abs(a.y - b.y) >= eps) return a.y < b.y;
    return a.x < b.x;
}

bool cmp4(Point a, Point b) {
    if (std::abs((a - res[1]).cross(b - res[1])) >= eps) return (a - res[1]).cross(b - res[1]) > 0;
    return (a - res[1]).vert() < (b - res[1]).vert();
}

std::deque<Point> Graham() {
    std::deque<Point> ret;
    std::sort(p + 1, p + n + 1, cmp1);
    std::sort(p + 2, p + n + 1, cmp2);
    p[n + 1] = p[1];
    /*
    printf("sorted:\n");
    for (int i = 1; i <= n + 1; i++) {
        printf("(%lf, %lf)\n", p[i].x, p[i].y);
    }
    printf("\n");
    */
    for (int i = 1; i <= n + 1; i++) {
        while (ret.size() >= 2 && (ret[ret.size() - 1] - ret[ret.size() - 2]).cross(p[i] - ret.back()) < 0) ret.pop_back();
        ret.push_back(p[i]);
    }
    return ret;
}

dbl disPointLine(Point p, Point a, Point b) {
    return std::abs((p - b).cross(b - a) / (b - a).vert());
}

Point feet(Point a, Point b, Point c) {
    dbl r = (c - a).dot(b - a) / (b - a).dot(b - a);
    return a + (b - a) * r;
}

void update(Point a, Point b, Point c, Point l, Point r) {
    Point tc = feet(a, b, c);
    Point tl = feet(a, b, l);
    Point tr = feet(a, b, r);
    /*
    printf("update \n");
    printf("tc(%lf, %lf)\n", tc.x, tc.y);
    printf("tl(%lf, %lf)\n", tl.x, tl.y);
    printf("tr(%lf, %lf)\n", tr.x, tr.y);
    printf("%lf * %lf = %lf\n", (c - tc).vert(), (tr - tl).vert(), std::abs((c - tc).vert() * (tr - tl).vert()));
    */
    if (ans > std::abs((c - tc).vert() * (tr - tl).vert())) {
        ans = std::abs((c - tc).vert() * (tr - tl).vert());
        res[1] = tl;
        res[2] = tr;
        res[3] = tl + (c - tc);
        res[4] = tr + (c - tc);
    }
    return;
}

void print() {
    std::sort(res + 1, res + 4 + 1, cmp3);
    std::sort(res + 2, res + 4 + 1, cmp4);
    std::cout << std::setiosflags(std::ios::fixed);
    std::cout << std::setprecision(5) << ans << '\n';
    for (int i = 1; i <= 4; i++) if (std::abs(res[i].x) < eps) res[i].x = 0;
    for (int i = 1; i <= 4; i++) if (std::abs(res[i].y) < eps) res[i].y = 0;
    for (int i = 1; i <= 4; i++) std::cout << std::setprecision(5) << res[i].x << ' ' << res[i].y << '\n';
    return;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> p[i].x >> p[i].y;
    std::deque<Point> ch = Graham();
    /*
    printf("ch:\n");
    for (auto i : ch) printf("(%lf, %lf)\n", i.x, i.y); printf("\n");
    */
    for (int i = 1, j = 1, k = 1, l = 1; i < ch.size(); i++) {
        while (disPointLine(ch[(j + 1) % ch.size()], ch[i - 1], ch[i]) >= disPointLine(ch[j], ch[i - 1], ch[i])) j = (j + 1) % ch.size();
        while (ch[(k + 1) % ch.size()].dot(ch[i] - ch[i - 1]) >= ch[k].dot(ch[i] - ch[i - 1])) k = (k + 1) % ch.size();
        l = std::max(l, j);
        while (ch[(l + 1) % ch.size()].dot(ch[i] - ch[i - 1]) <= ch[l].dot(ch[i] - ch[i - 1])) l = (l + 1) % ch.size();
        /*
        printf("i: (%lf, %lf)\n", ch[i].x, ch[i].y);
        printf("j: (%lf, %lf)\n", ch[j].x, ch[j].y);
        printf("k: (%lf, %lf)\n", ch[k].x, ch[k].y);
        printf("l: (%lf, %lf)\n", ch[l].x, ch[l].y);
        */
        update(ch[i - 1], ch[i], ch[j], ch[k], ch[l]);
    }
    print();
    return 0;
}