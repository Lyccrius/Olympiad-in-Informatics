#include <cstdio>
#include <algorithm>

const int maxN = 1e5;

const int inf = 1e9 + 10;

int N;
int h[maxN + 10];
int m[maxN + 10];
int s[maxN + 10];
double ans;

int main() {
    scanf("%d", &N);
    m[N + 1] = inf;
    for (int i = 1; i <= N; i++) scanf("%d", &h[i]);
    for (int i = N; i >= 1; i--) m[i] = std::min(h[i], m[i + 1]);
    for (int i = N; i >= 1; i--) s[i] = s[i + 1] + h[i];
    for (int i = 1; i <= N - 2; i++) ans = std::max(ans, 1.0 * (s[i + 1] - m[i + 1]) / (N - i - 1));
    for (int i = 1; i <= N - 2; i++) if (ans == 1.0 * (s[i + 1] - m[i + 1]) / (N - i - 1)) printf("%d\n", i);
    return 0;
}