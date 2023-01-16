#include <iostream>
#include <cstring>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 5;

int n;

struct Puzzle {
    int a[10][10];

    void Drop(int x, int y) {
        if (y == 0 || y >= 7) return;
        if (a[x][y - 1] != 0) return;
        if (a[x][y] == 0) return;
        int yy = y;
        while (yy - 1 >= 0 && a[x][yy - 1] == 0) yy--;
        std::swap(a[x][y], a[x][yy]);
        //printf("Drop(%d, %d) to (%d, %d)\n", x, y, x, yy);
        Drop(x, y + 1);
    }

    bool Del() {
        bool del = false;
        bool vis[10][10];
        std::memset(vis, false, sizeof(vis));
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                if (a[i][j] == 0) continue;
                if (i >= 1 && i <= 3 && a[i - 1][j] == a[i][j] && a[i][j] == a[i + 1][j]) {
                    vis[i - 1][j] = true;
                    vis[i + 1][j] = true;
                    vis[i][j] = true;
                    del = true;
                }
                if (j >= 1 && j <= 5 && a[i][j - 1] == a[i][j] && a[i][j] == a[i][j + 1]) {
                    vis[i][j - 1] = true;
                    vis[i][j + 1] = true;
                    vis[i][j] = true;
                    del = true;
                }
            }
        }
        if (del == false) return false;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                if (vis[i][j]) a[i][j] = 0;//, printf("Del (%d, %d)\n", i, j);
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 7; j++) {
                if (vis[i][j]) Drop(i, j + 1);
            }
        }
        Del();
        return true;
    }

    void Move(int x, int y, int g) {
        //printf("Move (%d, %d) to (%d, %d)\n", x, y, x + g, y);
        std::swap(a[x][y], a[x + g][y]);
        Drop(x, y + 1);
        Drop(x + g, y + 1);
        Drop(x + g, y);
        Drop(x, y);
        Del();
    }

    bool Check() {
        for (int i = 0; i < 5; i++) if (a[i][0] != 0) return false;
        return true;
    }
} Mayan;

struct Record {
    int a[10][10];

    void BackUp() {
        for (int i = 0; i < 5; i++) for (int j = 0; j < 7; j++) a[i][j] = Mayan.a[i][j];
        return;
    }

    void Restore() {
        for (int i = 0; i < 5; i++) for (int j = 0; j < 7; j++) Mayan.a[i][j] = a[i][j];
    }
} record[maxN + 10];

bool ok = false;

struct Step {
    int x, y;
    int g;
} ans[maxN + 10];

void print() {
    if (Mayan.Check() == false) return;
    ok = true;
    for (int i = 1; i <= n; i++) std::cout << ans[i].x << " " << ans[i].y << " " << ans[i].g << "\n";
    return;
}

void DFS(int now) {
    //printf("DFSing %d\n", now);
    for (int j = 6; j >= 0; j--) {
        for (int i = 0; i < 5; i++) {
            //if (Mayan.a[i][j]) printf("%d ", Mayan.a[i][j]);
            //else printf("  ");
        }
        //printf("\n");
    }
    if (ok) return;
    if (now >= n) {
        print();
        return;
    }
    record[now].BackUp();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 7; j++) {
            if (Mayan.a[i][j] == 0) continue;
            if (i < 4 && Mayan.a[i + 1][j] != Mayan.a[i][j]) {
                Mayan.Move(i, j, 1);
                ans[now + 1] = (Step) {i, j, 1};
                DFS(now + 1);
                record[now].Restore();
            }
            if (i > 0 && Mayan.a[i - 1][j] == 0) {
                Mayan.Move(i, j, -1);
                ans[now + 1] = (Step) {i, j, -1};
                DFS(now + 1);
                record[now].Restore();
            }
        }
    }
}

int main() {
    promote();
    std::cin >> n;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j <= 7; j++) {
            std::cin >> Mayan.a[i][j];
            if (Mayan.a[i][j] == 0) break;
        }
    }
    DFS(0);
    if (ok == false) std::cout << -1 << "\n";
    return 0;
}