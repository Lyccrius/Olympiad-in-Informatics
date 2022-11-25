#include <cstdio>
#include <algorithm>

const int maxN = 30 + 10;
const int maxV = 2e4 + 10;

int V;
int n;
int v[maxN];
int f[maxV];

int main() {
    scanf("%d", &V);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
    for (int i = 1; i <= n; i++) {
        for (int j = V; j >= v[i]; j--) {
            if (f[j - v[i]] + v[i] <= V) f[j] = std::max(f[j], f[j - v[i]] + v[i]);
        }
    }
    printf("%d\n", V - f[V]);
    return 0;
}