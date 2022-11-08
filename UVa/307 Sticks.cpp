#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxn = 65 + 10;

int n;
int a[maxn];

int maxA;
int sum;
int len;
int num;
bool vis[maxn];

bool cmp(int a, int b) {
    return a > b;
}

bool DFS(int cnt, int now, int choice) {
    if (cnt > num) return true;
    if (now == len) return DFS(cnt + 1, 0, 1);
    int failness = 0;
    for (int i = choice; i <= n; i++) {
        if (!vis[i] && now + a[i] <= len && failness != a[i]) {
            vis[i] = true;
            if (DFS(cnt, now + a[i], i + 1)) return true;
            vis[i] = false;
            failness = a[i];
            if (now == 0 || now + a[i] == len) return false;
        }
    }
    return false;
}

int main() {
    while (scanf("%d", &n) && n){
        maxA = 0;
        sum = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            if (a[i] > 50) {
                i--;
                continue;
            }
            maxA = std::max(maxA, a[i]);
            sum += a[i];
        }
        std::sort(a + 1, a + n + 1, cmp);
        for (len = maxA; len <= sum; len++) {
            if (sum % len) continue;
            num = sum / len;
            std::memset(vis, false, sizeof(vis));
            if (DFS(1, 0, 1)) break;
        }
        printf("%d\n", len);
    }
    return 0;
}