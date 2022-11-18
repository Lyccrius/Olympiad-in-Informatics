#include <cstdio>
#include <cmath>
#include <cstring>

const int maxN = 16 * 2 + 10;

int n;

int a[maxN];
bool visited[maxN];
bool isPrime[maxN] = {  false, false, true, true, false, true, false, true, false, false,
                        false, true, false, true, false, false, false, true, false, true,
                        false, false, false, true, false, false, false, false, false, true,
                        false, true, false, false};

void DFS(int cur) {
    if (cur > n) {
        if (isPrime[a[1] + a[n]]){
            for (int i = 1; i < n; i++) printf("%d ", a[i]);
            printf("%d\n", a[n]);
        }
        return;
    } else for (int i = 2; i <= n; i++) if (!visited[i] && isPrime[i + a[cur - 1]]) {
        a[cur] = i;
        visited[i] = true;
        DFS(cur + 1);
        visited[i] = false;
    }
    return;
}

int main() {
    int kase = 0;
    while (scanf("%d", &n) != EOF) {
        if (kase) printf("\n");
        kase++;
        printf("Case %d:\n", kase);
        std::memset(visited, 0, sizeof(visited));
        a[1] = 1;
        DFS(2);
    }
    return 0;
}