#include <iostream>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> dic;
typedef long long lxl;

const int maxN = 2e6;


int T;
lxl N, M;
lxl A[maxN + 10];
dic E[maxN + 10];
int u, v;
int fir;
int sec;

void init() {
    for (int i = 1; i <= N; i++) E[i].clear();
    fir = 0;
    sec = 0;
    return;
}

void mian() {
    std::cin >> N >> M;
    init();
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i < N; i++) {
        std::cin >> u >> v;
        E[u].push_back(v);
        E[v].push_back(u);
    }
    for (int i = 1; i <= N; i++) {
        if (A[fir] < A[i]) {
            fir = i;
        }
        if (A[fir] == A[i] && fir > i) {
            fir = i;
        }
    }
    for (auto i : E[fir]) {
        if (A[sec] < A[i]) {
            sec = i;
        }
        if (A[sec] == A[i] && sec > i) {
            sec = i;
        }
    }
    if (!sec) {
        std::cout << fir << '\n';
        return;
    }
    M -= A[fir] - A[sec];
    if (fir < sec) M--;
    if (M < 0) {
        std::cout << fir << '\n';
    } else if (M & 1) {
        std::cout << fir << '\n';
    } else {
        std::cout << sec << '\n';
    }
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}