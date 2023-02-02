#include <iostream>

const int maxH = 1000;
const int maxW = 1000;

int H, W, A, B;
int M[maxH + 10][maxW + 10];

int main() {
    std::cin >> H >> W >> A >> B;
    for (int i = 1; i <= B; i++) for (int j = A + 1; j <= W; j++) M[i][j] = 1;
    for (int i = B + 1; i <= H; i++) for (int j = 1; j <= A; j++) M[i][j] = 1;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) std::cout << M[i][j];
        std::cout << '\n';
    }
    return 0;
}