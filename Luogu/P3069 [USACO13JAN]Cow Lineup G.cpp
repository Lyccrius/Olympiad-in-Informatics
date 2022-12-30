#include <cstdio>
#include <algorithm>
#include <map>

const int inf = 1e9 + 10;

const int maxN = 1e5;

int N, K;
int ID[maxN + 10];

std::map<int, bool> vis;
std::map<int, int> cnt;

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) scanf("%d", &ID[i]);
    int l = 1;
    int r = 0;
    int tot = 0;
    int ans = 0;
    while (r < N) {
        while (tot < K + 2 && r < N) {
            r++;
            if (cnt[ID[r]] == 0) tot++;
            cnt[ID[r]]++;
            ans = std::max(ans, cnt[ID[r]]);
        }
        while (tot == K + 2 && l < r) {
            cnt[ID[l]]--;
            if (cnt[ID[l]] == 0) tot--;
            l++;
        }
    }
    printf("%d\n", ans);
    return 0;
}