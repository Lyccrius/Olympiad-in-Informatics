#include <cstdio>
#include <cstring>
#include <algorithm>

const int maxN = 500 + 10;
const int maxM = 500 + 10;

int dx[5] = {0, 1, 0, -1};
int dy[5] = {1, 0, -1, 0};

int N, M;
int H[maxN][maxM];
int l[maxN][maxM];
int r[maxN][maxM];
int vis[maxN][maxM];
int cnt;

void DFS(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 4; i++) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx < 1 || xx > N) continue;
        if (yy < 1 || yy > M) continue;
        if (H[xx][yy] >= H[x][y]) continue;
        if (!vis[xx][yy]) DFS(xx, yy);
        l[x][y] = std::min(l[x][y], l[xx][yy]);
        r[x][y] = std::max(r[x][y], r[xx][yy]);
    }
    return;
}

int main() {
    std::memset(l, 0x3f, sizeof(l));
    std::memset(r, 0xcf, sizeof(r));
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) scanf("%d", &H[i][j]);
    for (int i = 1; i <= M; i++) l[N][i] = i;
    for (int i = 1; i <= M; i++) r[N][i] = i; 
    for (int i = 1; i <= M; i++) DFS(1, i);
    for (int i = 1; i <= M; i++) if (!vis[N][i]) cnt++;
    if (cnt) {
        printf("%d\n", 0);
        printf("%d\n", cnt);
        return 0;
    }
    int last = 1;
    while (last <= M) {
        int maxR = 0;
        for (int i = 1; i <= M; i++) if (last >= l[1][i]) maxR = std::max(maxR, r[1][i]);
        cnt++;
        last = maxR + 1;
    }
    printf("%d\n", 1);
    printf("%d\n", cnt);
    return 0;
}