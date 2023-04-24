#include "triangles.h"
#include <algorithm>

typedef long long lxl;

const int maxN = 4000;
const int maxM = 4000;

struct Point {
    int x, y;
    int id;

    Point operator -(const Point &other) const {
        return (Point) {x - other.x, y - other.y};
    }

    lxl operator *(const Point &other) const {
        return 1ll * x * other.y - 1ll * y * other.x;
    }

    bool operator <(const Point &other) const {
        if ((y > 0) != (other.y > 0)) return (y > 0) > (other.y > 0);
        return *this * other > 0;
    }
} p[maxN + maxM + 10];

void check_triangles(int n, int m, int *rx, int *ry, int *bx, int *by, int **result) {
    for (int i = 0; i < n; i++) {
        p[i].x = rx[i];
        p[i].y = ry[i];
        p[i].id = i;
    }
    for (int i = 0; i < m; i++) {
        p[i + n].x = bx[i];
        p[i + n].y = by[i];
        p[i + n].id = i + n;
    }
    std::sort(p, p + n + m);
    for (int i = 0; i < n + m; i++) {
        if (p[i].id >= n) continue;
        bool flag = false;
        Point t;
        for (int j = (i + 1) % (n + m); j != i; j = (j + 1) % (n + m)) {
            if (p[i] * p[j] <= 0) break;
            if (p[j].id >= n) {
                if (!flag || (t - p[i]) * (p[j] - p[i]) > 0) {
                    t = p[j];
                }
                flag = true;
            } else {
                if (flag && (p[j] - p[i]) * (t - p[i]) > 0) {
                    int a = std::min(p[i].id, p[j].id);
                    int b = std::max(p[i].id, p[j].id);
                    result[a][b] = t.id - n;
                } else {
                    int a = std::min(p[i].id, p[j].id);
                    int b = std::max(p[i].id, p[j].id);
                    result[a][b] = -1;
                }
            }
        }
    }
    return;
}