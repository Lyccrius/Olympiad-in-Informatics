#include <cstdio>

const int maxN = 13 + 20;

int n;

int board[maxN];
int place[maxN];
int slope[maxN];
int epols[maxN];
int cnt;

void DFS(int line) {
    if (line > n) {
        cnt++;
        if (cnt <= 3) {
            for (int i = 1; i <= n; i++) printf("%d ", board[i]);
            printf("\n");
        }
        return;
    }
    for (int i = 1; i <= n; i++) if (!place[i] && !slope[line + i - 1] && !epols[line - i + n - 1]) {
        place[i] = 1;
        slope[i + line - 1] = 1;
        epols[line - i + n - 1] = 1;
        board[line] = i;
        DFS(line + 1);
        place[i] = 0;
        slope[i + line - 1] = 0;
        epols[line - i + n - 1] = 0;
        board[line] = 0;
    }
    return;
}

int main() {
    scanf("%d", &n);
    DFS(1);
    printf("%d\n", cnt);
    return 0;
}