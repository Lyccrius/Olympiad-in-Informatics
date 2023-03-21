#include <iostream>

const int maxN = 100;

int N;
int M;
int S;

int main() {
    std::cin >> N;
    if (N & 1) {
        S = N;
    } else {
        S = N + 1;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (i + j != S) {
                M++;
            }
        }
    }
    std::cout << M << '\n';
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            if (i + j != S) {
                std::cout << i << ' ' << j << '\n';
            }
        }
    }
    return 0;
}