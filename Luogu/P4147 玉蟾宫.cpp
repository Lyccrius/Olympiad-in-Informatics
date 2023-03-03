#include <iostream>
#include <deque>
#include <algorithm>

typedef long long lxl;

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;
const int maxM = 1000;

int N, M;
int S;
int a[maxN + 10][maxM + 10];
int u[maxN + 10][maxM + 10];

struct Node {
    int h;
    int w;
};

int main() {
    promote();
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            char ch;
            std::cin >> ch;
            if (ch == 'F') a[i][j] = true;
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (a[i][j]) {
                u[i][j] = u[i - 1][j] + 1;
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        std::deque<Node> q;
        int w, h;
        for (int j = 1; j <= M; j++) {
            w = 0;
            while (q.size() && q.back().h >= u[i][j]) {
                w += q.back().w;
                h = q.back().h;
                S = std::max(S, w * h);
                q.pop_back();
            }
            q.push_back((Node) {u[i][j], w + 1});
        }
        w = 0;
        while (q.size()) {
            w += q.back().w;
            S = std::max(S, w * q.back().h);
            q.pop_back();
        }
    }
    std::cout << 3 * S;
    return 0;
}