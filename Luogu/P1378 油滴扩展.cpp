#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>

const int maxN = 6 + 10;
const double pi = 3.1415926535;

int n;
double xa, ya, xb, yb;
double x[maxN], y[maxN], r[maxN];
bool vis[maxN];
double s;
double ans;

double cal(int i) {
    double s1 = std::min(std::abs(x[i] - xa), std::abs(x[i] - xb));
    double s2 = std::min(std::abs(y[i] - ya), std::abs(y[i] - yb));
    double res = std::min(s1, s2);
    for (int j = 1; j <= n; j++) if (i != j && vis[j]) {
        double d = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        res = std::min(res, std::max(d - r[j], 0.0));
    }
    return res;
}

void DFS(int now, double sum) {
    if (now > n) {
        ans = std::max(ans, sum);
        return;
    }
    for (int i = 1; i <= n; i++) if (!vis[i]) {
        r[i] = cal(i);
        vis[i] = true;
        DFS(now + 1, sum + r[i] * r[i] * pi);
        vis[i] = false;
    }
    return;
}

int main() {
    scanf("%d", &n);
    scanf("%lf%lf%lf%lf", &xa, &ya, &xb, &yb);
    s = std::abs(xa - xb) * std::abs(ya - yb); 
    for (int i = 1; i <= n; i++) scanf("%lf%lf", &x[i], &y[i]);
    DFS(1, 0);
    printf("%d", (int)(s - ans + 0.5));
    return 0;
}