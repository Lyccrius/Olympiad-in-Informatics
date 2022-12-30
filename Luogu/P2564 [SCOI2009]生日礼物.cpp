#include <cstdio>
#include <algorithm>
#include <map>

const int inf = 1e9 + 10;

const int maxN = 1e6;
const int maxK = 60 + 10;

int N, K;
int T[maxK + 10];

struct Node {
    int X;
    int Type;

    bool operator<(const Node& other) const {
        return X < other.X;
    }
} bead[maxN + 10];
int head;

std::map<int, int> cnt;

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= K; i++) {
        scanf("%d", &T[i]);
        int pos;
        for (int j = 1; j <= T[i]; j++) scanf("%d", &pos), bead[++head] = (Node){pos, i};
    }
    std::sort(bead + 1, bead + N + 1);
    int l = 1;
    int r = 0;
    int tot = 0;
    int ans = inf;
    while (r < N) {
        while (tot < K && r < N) {
            r++;
            if (cnt[bead[r].Type] == 0) tot++;
            cnt[bead[r].Type]++;
        }
        while (tot == K && l < r) {
            ans = std::min(ans, bead[r].X - bead[l].X);
            cnt[bead[l].Type]--;
            if (cnt[bead[l].Type] == 0) tot--;
            l++;
        }
    }
    printf("%d\n", ans);
    return 0;
}