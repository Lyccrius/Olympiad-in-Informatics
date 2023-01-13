#include <cstdio>
#include <algorithm>

long long a, b;

int dep;
bool ok;
long long res[20];
long long ans[20];

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

void DFS(long long a, long long b, int now) {
    if (now > dep) return;
    if (a == 1 && b > res[now - 1]) {
        res[now] = b;
        if (ok == false || res[now] < ans[now]) for (int  i = 1; i <= dep; i++) ans[i] = res[i];
        ok = true;
        return;
    }
    long long l = std::max(res[now - 1] + 1, b / a);
    long long r = (dep - now + 1) * b / a;
    if (ok && r >= ans[dep]) r = ans[dep] - 1;
    for (long long i = l; i < r; i++) {
        res[now] = i;
        long long c = gcd(a * i - b, b * i);
        DFS((a * i - b) / c, b * i / c, now + 1);
    }
    return;
}

int main() {
    scanf("%lld%lld", &a, &b);
    long long c = gcd(a, b);
    a /= c;
    b /= c;
    res[0] = 1;
    for (dep = 1; dep <= 10; dep++) {
        DFS(a, b, 1);
        if (ok) {
            for (int i = 1; i <= dep; i++) printf("%lld ", ans[i]);
            break;
        }
    }
    return 0;
}