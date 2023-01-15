#include <iostream>
#include <algorithm>
#include <vector>

int row[10];
int col[10];
int gid[10];
int mat[10][10];
int vis[10][10];

void promote(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

int grid(int x, int y) {
    int ret = 0;
    ret += (x - 1) / 3 * 3;
    ret += (y - 1) / 3 + 1;
    return ret;
}

int score(int x, int y) {
    x = std::abs(x - 5);
    y = std::abs(y - 5);
    return 10 - std::max(x, y);
}

int pos(int x, int y) {
    int ret = (1 << 10) - 1;
    ret &= row[x];
    ret &= col[y];
    ret &= gid[grid(x, y)];
    //printf("pos(%d, %d):\n", x, y);
    //for (int i = 1; i <= 9; i++) if ((ret >> i) & 1) printf("%d ", i);
    //printf("\n");
    return ret;
}

int popcount(int x) {
    int ret = 0;
    for (int i = 1; i <= 9; i++) if ((x >> i) == 1) ret++;
    return ret;
}

struct Node {
    int x, y;
    
    bool operator<(const Node &other) const {
        return popcount(pos(x, y)) < popcount(pos(other.x, other.y));
    }
};

std::vector<Node> q;

int tot = 0;
int res = 0;
int ans = -1;

void fill(int x, int y, int val) {
    row[x] ^= 1 << val;
    col[y] ^= 1 << val;
    gid[grid(x, y)] ^= 1 << val;
    return;
}

void DFS(int now) {
    //printf("----------\n");
    //printf("DFSing %d\n", dep);
    if (now == q.size()) {
        ans = std::max(ans, res);
        //printf("tot = %d, res = %d\n", tot, res);
        return;
    }
    int x = q[now].x;
    int y = q[now].y;
    int p = pos(x, y);
    //printf("to (%d, %d)\n", x, y);
    for (int i = 1; i <= 9; i++) if ((p >> i) & 1) {
        //printf("fill (%d, %d), %d\n", x, y, i);
        fill(x, y, i), res += i * score(x, y);
        //printf("fill %d at (%d, %d)\n", i, x, y);
        DFS(now + 1);
        fill(x, y, i), res -= i * score(x, y);
        //printf("remv (%d, %d), %d\n", x, y, i);
    }
    return;
}

int main() {
    promote();
    
    for (int i = 1; i <= 9; i++) {
        row[i] = (1 << 10) - 1;
        col[i] = (1 << 10) - 1;
        gid[i] = (1 << 10) - 1;
    }
    
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            std::cin >> mat[i][j];
            if (mat[i][j] != 0) fill(i, j, mat[i][j]), res += mat[i][j] * score(i, j);
            else q.push_back((Node) {i, j});
        }
    }
    std::sort(q.begin(), q.end());
    DFS(0);
    printf("%d\n", ans);
    return 0;
}