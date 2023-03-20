#include <iostream>
#include <deque>

typedef char chr;

const int maxH = 1000;
const int maxW = 1000;

const int dx[5] = {0, 0, 1, 0, - 1};
const int dy[5] = {0, 1, 0, - 1, 0};

int H, W;
chr A[maxH + 10][maxW + 10];
int B[maxH + 10][maxW + 10];
int C[maxH + 10][maxW + 10];
int ans;

struct Node {
    int x, y;
};

std::deque<Node> q;

int main() {
    std::cin >> H >> W;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            std::cin >> A[i][j];
        }
    }
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            if (A[i][j] == '#') {
                B[i][j] = true;
                C[i][j] = 0;
                q.push_back((Node) {i, j});
            }
        }
    }
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        q.pop_front();
        //if (A[x][y] == '#') continue;
        if (x < 1 || x > H) continue;
        if (y < 1 || y > W) continue;
        ans = std::max(ans, C[x][y]);
        for (int i = 1; i <= 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (A[xx][yy] == '#') continue;
            if (B[xx][yy]) continue;
            A[xx][yy] = '#';
            B[xx][yy] = true;
            C[xx][yy] = C[x][y] + 1;
            q.push_back((Node) {xx, yy});
        }
    }
    std::cout << ans;
    return 0;
}