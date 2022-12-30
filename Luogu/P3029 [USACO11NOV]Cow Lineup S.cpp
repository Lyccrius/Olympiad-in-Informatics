#include <cstdio>
#include <algorithm>
#include <map>

const int inf = 1e9 + 10;

const int maxN = 50000;

int N;
struct Node {
    int X;
    int ID;

    bool operator<(const Node& other) const {
        return X < other.X;
    }
} cow[maxN + 10];

std::map<int, bool> vis;
std::map<int, int> cnt;

int rangeX[maxN + 10];
int totX;

int totID;

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) scanf("%d%d", &cow[i].X, &cow[i].ID);
    for (int i = 1; i <= N; i++) rangeX[i] = cow[i].X;
    std::sort(rangeX + 1, rangeX + N + 1);
    totX = std::unique(rangeX + 1, rangeX + N + 1) - rangeX - 1;
    for (int i = 1; i <= N; i++) cow[i].X = std::lower_bound(rangeX + 1, rangeX + N + 1, cow[i].X) - rangeX;
    for (int i = 1; i <= N; i++) {
        if (vis[cow[i].ID] == false) totID++;
        vis[cow[i].ID] = true;
    }
    std::sort(cow + 1, cow + N + 1);
    int l = 1;
    int r = 0;
    int tot = 0;
    int ans = inf;
    while (r < N) {
        while (tot < totID && r < N) {
            r++;
            if (cnt[cow[r].ID] == 0) tot++;
            cnt[cow[r].ID]++;
        }
        while (tot == totID && l < r) {
            ans = std::min(ans, rangeX[cow[r].X] - rangeX[cow[l].X]);
            cnt[cow[l].ID]--;
            if (cnt[cow[l].ID] == 0) tot--;
            l++;
        }
    }
    printf("%d\n", ans);
    return 0;
}