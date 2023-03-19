#include <iostream>
#include <algorithm>

const int maxN = 1e5;

int N, C, K;
int T[maxN + 10];
int last;
int cnt;
int ans;

int main() {
    std::cin >> N >> C >> K; last = - K;
    for (int i = 1; i <= N; i++) std::cin >> T[i];
    std::sort(T + 1, T + N + 1);
    for (int i = 1; i <= N; i++) {
        if (last + K < T[i] || cnt == C) {
            last = T[i];
            cnt = 0;
            ans++;
        }
        cnt++;
    }
    std::cout << ans;
    return 0;
}