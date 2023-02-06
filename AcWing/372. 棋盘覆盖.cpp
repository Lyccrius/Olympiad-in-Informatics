#include <iostream>

typedef std::pair<int, int> pii;

const int maxN = 100;
const int maxT = 100;
const int dx[5] = {0, -1, 0, 1, 0};
const int dy[5] = {0, 0, 1, 0, -1};

int N, t;
int x, y;
int ans;

namespace graph {
    struct Vertex {
        bool banned;
        bool vis;
        pii match;
    } vertex[maxN + 10][maxN + 10];

    void init() {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                vertex[i][j].vis = false;
            }
        }
        return;
    }

    bool KM(int x, int y) {
        //printf("KM(%d, %d)\n", x, y);
        //printf("match = (%d, %d)\n", vertex[x][y].match.first, vertex[x][y].match.second);
        for (int i = 1; i <= 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (xx < 1 || xx > N) continue;
            if (yy < 1 || yy > N) continue;
            if (vertex[xx][yy].vis) continue;
            if (vertex[xx][yy].banned) continue;
            vertex[xx][yy].vis = true;
            pii t = vertex[xx][yy].match;
            if (t.first == 0 || KM(t.first, t.second)) {
                vertex[xx][yy].match = std::make_pair(x, y);
                //("matched (%d, %d) with (%d, %d)\n", xx, yy, x, y);
                return true;
            }
        }
        return false;
    }
}

int main() {
    std::cin >> N >> t;
    for (int i = 1; i <= t; i++) std::cin >> x >> y, graph::vertex[x][y].banned = true;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if ((i + j) % 2 && !graph::vertex[i][j].banned) {
                //printf("considering(%d, %d)\n", i, j);
                graph::init();
                if (graph::KM(i, j)) ans++;
            }
        }
    }
    std::cout << ans;
    return 0;
}