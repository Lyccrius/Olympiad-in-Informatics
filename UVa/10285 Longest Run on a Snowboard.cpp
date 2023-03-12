#include <iostream>
#include <algorithm>
#include <string>

typedef std::string str;
typedef char chr;

const int maxR = 100;
const int maxC = 100;
const int dx[5] = {0, 0, -1, 0, 1};
const int dy[5] = {0, 1, 0, -1, 0};

int N;
chr S[maxR + 10]; int R, C;
int A[maxR + 10][maxC + 10];
int B[maxR + 10][maxC + 10];
int ans;

int DFS(int x, int y) {
    if (B[x][y]) return B[x][y];
    B[x][y] = 1;
    for (int i = 1; i <= 4; i++) {
        int x_ = x + dx[i];
        int y_ = y + dy[i];
        if (x_ < 1 || x_ > R) continue;
        if (y_ < 1 || y_ > C) continue;
        if (A[x][y] > A[x_][y_]) B[x][y] = std::max(B[x][y], DFS(x_, y_) + 1);
    }
    return B[x][y];
}

void mian() {
    ans = 0;
    std::fill(B[0], B[0] + (maxR + 10) * (maxC + 10), 0);
    std::cin >> S >> R >> C;
    //std::cin >> R >> C;
    for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) std::cin >> A[i][j];
    for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) ans = std::max(ans, DFS(i, j));
    std::cout << S << ": " << ans << '\n';
}

int main() {
    std::cin >> N;
    while (N--) 
    mian();
    return 0;
}