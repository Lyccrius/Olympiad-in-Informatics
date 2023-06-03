#include <iostream>
#include <deque>

typedef char chr;
typedef long long lxl;
typedef std::pair<int, int> pii;

const int maxN = 1500;
const int maxM = 1500;
const int rx[5] = {0, 0, 0, 1};
const int ry[5] = {0, -1, 1, 0};
const int bx[5] = {0, 1, -1, 0};
const int by[5] = {0, 0, 0, 1};

int n, m;
chr a[maxN + 10][maxM + 10];
int v[maxN + 10][maxM + 10];
lxl ans = 0;

bool check(int x1, int y1, int x2, int y2) {
    //printf("check(%d, %d, %d, %d)\n", x1, y1, x2, y2);
    std::deque<pii> q;
    for (int j = y1; j <= y2; j++) if (a[x1 - 1][j] != 'R' || a[x2 + 1][j] != 'R') return false;
    for (int i = x1; i <= x2; i++) if (a[i][y1 - 1] != 'B' || a[i][y2 + 1] != 'B') return false;
    std::fill(v[0], v[0] + sizeof(v) / 4, 0);
    //for (int j = y1; j <= y2; j++) q.push_back(std::make_pair(x1 - 1, j));
    q.push_back(std::make_pair(x1 - 1, y1));
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop_front();
        if (v[x][y]) continue;
        v[x][y] = true;
        //printf("BFS(%d, %d)\n", x, y);
        for (int i = 1; i <= 3; i++) {
            int xx = x + rx[i];
            int yy = y + ry[i];
            if (yy < y1) continue;
            if (yy > y2) continue;
            if (a[xx][yy] != 'R') continue;
            if (xx > x2) return false;
            if (v[xx][yy]) continue;
            q.push_back(std::make_pair(xx, yy));
        }
    }
    q.clear();
    std::fill(v[0], v[0] + sizeof(v) / 4, 0);
    q.push_back(std::make_pair(x1, y1 - 1));
   //for (int i = x1; i <= x2; i++) q.push_back(std::make_pair(i, y1 - 1)), v[i][y1 - 1] = true;
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop_front();
        if (v[x][y]) continue;
        v[x][y] = true;
        for (int i = 1; i <= 3; i++) {
            int xx = x + bx[i];
            int yy = y + by[i];
            if (xx < x1) continue;
            if (xx > x2) continue;
            if (a[xx][yy] != 'B') continue;
            if (yy > y2) return false;
            if (v[xx][yy]) continue;
            q.push_back(std::make_pair(xx, yy));
        }
    }
    return true;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) std::cin >> a[i][j];
    for (int x1 = 2; x1 <= n - 1; x1++) {
        for (int x2 = x1; x2 <= n - 1; x2++) {
            for (int y1 = 2; y1 <= m - 1; y1++) {
                for (int y2 = y1; y2 <= m - 1; y2++) {
                    if (check(x1, y1, x2, y2)) ans++;
                }
            }
        }
    }
    std::cout << ans << '\n';
    return 0;
}