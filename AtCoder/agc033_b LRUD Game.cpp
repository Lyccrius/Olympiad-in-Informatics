#include <iostream>
#include <algorithm>

typedef char chr;

const int maxH = 2e5;
const int maxW = 2e5;
const int maxN = 2e5;

int H, W, N;
int sr, sc;
chr S[maxN + 10];
chr T[maxN + 10];
int U, D, L, R;

int main() {
    std::cin >> H >> W >> N;
    std::cin >> sr >> sc;
    std::cin >> (S + 1);
    std::cin >> (T + 1);
    U = 1;
    D = H;
    L = 1;
    R = W;
    for (int i = N; i >= 1; i--) {
        if (T[i] == 'U') D = std::min(D + 1, H);
        if (T[i] == 'D') U = std::max(U - 1, 1);
        if (T[i] == 'L') R = std::min(R + 1, W);
        if (T[i] == 'R') L = std::max(L - 1, 1);
        if (S[i] == 'U') U++;
        if (S[i] == 'D') D--;
        if (S[i] == 'L') L++;
        if (S[i] == 'R') R--;
        if (U > D || L > R) {
            std::cout << "NO" << '\n';
            return 0;
        }
    }
    if (sr < U || sr > D || sc < L || sc > R) {
        std::cout << "NO" << '\n';
    } else {
        std::cout << "YES" << '\n';
    }
    return 0;
}