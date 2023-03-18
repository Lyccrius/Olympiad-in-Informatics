#include <iostream>
#include <algorithm>

const int maxN = 1e3;

int n, k, m;
int a[maxN + 10];
int pre[maxN + 10];
int suf[maxN + 10];
int ans;

bool check() {
    //printf("check: "); for (int i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n");
    for (int i = 0; i <= n + 1; i++) pre[i] = i - 1;
    for (int i = 0; i <= n + 1; i++) suf[i] = i + 1;
    int tot = n;
    int del[maxN + 10];
    int now;
    for (int i = 1; i <= k; i++) {
        if (tot == 1) return false;
        now = suf[0];
        while (now <= n) {
            del[now] = false;
            now = suf[now];
        }
        now = suf[0];
        while (now <= n) {
            if (a[now] < a[pre[now]]) del[now] = true;
            if (a[now] < a[suf[now]]) del[now] = true;
            now = suf[now];
        }
        now = suf[0];
        while (now <= n) {
            if (del[now]) {
                tot--;
                suf[pre[now]] = suf[now];
                pre[suf[now]] = pre[now];
            }
            now = suf[now];
        }
    }
    return tot == 1;
}

int main() {
    std::cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) a[i] = i;
    do {
        if (check()) ans = (ans + 1) % m;
    } while (std::next_permutation(a + 1, a + n + 1));
    std::cout << ans;
    return 0;
}