#include <iostream>

typedef long long lxl;

const int maxN = 300;

int N;
int A[maxN + 10][maxN + 10];
int B[maxN + 10][maxN + 10];
lxl S;

int main() {
    std::cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            std::cin >> A[i][j];
        }
    }
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (i != k && j != k && i != j) {
                    if (A[i][j] == A[i][k] + A[k][j]) {
                        B[i][j] = true;
                    }
                    if (A[i][j] > A[i][k] + A[k][j]) {
                        std::cout << -1;
                        return 0;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i != j) {
                if (!B[i][j]) {
                    S += A[i][j];
                }
            }
        }
    }
    std::cout << S / 2;
    return 0;
}