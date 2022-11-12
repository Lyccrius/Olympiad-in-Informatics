#include <cstdio>

const int maxn = 60 + 10;

int kase = 0;

int N;
int start[maxn];
int end[maxn];

long long f(int *P, int i, int final) {
    if (i == 0) return 0;
    if (P[i] == final) return f(P, i - 1, final);
    return f(P, i - 1, 6 - P[i] - final) + ((long long)1 << (i - 1));
}

int main() {
    while (scanf("%d", &N) == 1 && N) {
        kase++;
        for (int i = 1; i <= N; i++) scanf("%d", &start[i]);
        for (int i = 1; i <= N; i++) scanf("%d", &end[i]);
        int k = N;
        while (k && start[k] == end[k]) k--;
        long long ans = 0;
        if (k >= 1) {
            int other = 6 - start[k] - end[k];
            ans = f(start, k - 1, other) + f(end, k - 1, other) + 1;
        }
        printf("Case %d: %lld\n", kase, ans);
    }
    return 0;
}