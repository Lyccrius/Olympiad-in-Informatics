#include <cstdio>
#include <cstring>

const int maxN = 1500 + 10;

int N, M;
char maze[maxN][maxN];
bool vis[maxN][maxN];
bool exVis[maxN * 2][maxN * 2];
int Sx, Sy;

bool DFS(int x, int y) {
    if (x == -1) return DFS(N * 2 - 1, y);
    if (y == -1) return DFS(x, M * 2 - 1);
    if (x == N * 2) return DFS(0, y);
    if (y == M * 2) return DFS(x, 0);
    if (maze[x % N][y % M] == '#') return false;
    if (exVis[x][y]) return false;
    if (vis[x % N][y % M]) return true;
    vis[x % N][y % M] = true;
    exVis[x][y] = true;
    if (DFS(x - 1, y)) return true;
    if (DFS(x + 1, y)) return true;
    if (DFS(x, y - 1)) return true;
    if (DFS(x, y + 1)) return true;
    return false;
}

int main() {
    while (scanf("%d%d", &N, &M) != EOF) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                scanf(" %c", &maze[i][j]);
                if (maze[i][j] == 'S') {
                    Sx = i;
                    Sy = j;
                }
            }
        }
        std::memset(vis, 0, sizeof(vis));
        std::memset(exVis, 0, sizeof(exVis));
        if (DFS(Sx, Sy)) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}