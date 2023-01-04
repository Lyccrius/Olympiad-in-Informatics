#include <cstdio>
#include <deque>

const int inf = 1e4;
const double eps = 1e-6;

const int maxN = 1e5;

int n;
int S, T;
int a[maxN + 10];

bool check(double v) {
    double pre[maxN + 10];
    pre[0] = 0;
    for (int i = 1; i <= n; i++) pre[i] = pre[i - 1] + a[i] - v;
    std::deque<int> q;
    for (int i = 1; i + S - 1<= n; i++) {
        int j = i + S - 1;
        while (q.size() && pre[q.back()] > pre[i - 1]) q.pop_back();
        while (q.size() && j - q.front() > T) q.pop_front();
        q.push_back(i - 1);
        if (pre[j] - pre[q.front()] > 0) return true;
    }
    return false;
}

int main() {
    scanf("%d", &n);
    scanf("%d%d", &S, &T);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    double l = -inf;
    double r = inf;
    while (r - l >= eps) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    printf("%.3lf", l);
    return 0;
}