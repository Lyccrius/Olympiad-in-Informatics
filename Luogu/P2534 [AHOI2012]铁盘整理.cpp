#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 16;
const int maxR = 100;

int N;
int R[maxN + 10];
bool ok;
int step;

void discrete() {
    std::vector<int> range;
    for (int i = 1; i <= N; i++) range.push_back(R[i]);
    std::sort(range.begin(), range.end());
    for (int i = 1; i <= N; i++) R[i] = std::lower_bound(range.begin(), range.end(), R[i]) - range.begin() + 1;
    return;
}

int h() {
    int ret = 0;
    for (int i = 1; i <= N; i++) if (std::abs(R[i] - R[i + 1]) != 1) ret++;
    return ret;
}

void DFS(int now, int last) {
    if (now == step) {
        if (h() == 0) ok = true;
        return;
    }
    for (int i = 2; i <= N; i++) {
        if (i == last) continue;
        std::reverse(R + 1, R + i + 1);
        if (now + h() <= step) DFS(now + 1, i);
        std::reverse(R + 1, R + i + 1);
    }
    return;
}

int main() {
    promote();
    std::cin >> N;
    for (int i = 1; i <= N; i++) std::cin >> R[i];
    discrete();
    R[N + 1] = N + 1;
    for (step = 0; ok == false; step++) {
        DFS(0, 0);
        if (ok) break;
    }
    std::cout << step << "\n";
    return 0;
}