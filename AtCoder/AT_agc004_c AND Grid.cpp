#include <iostream>

typedef char chr;

const int maxH = 500;
const int maxW = 500;

int H, W;
chr a[maxH + 10][maxW + 10];
chr b[maxH + 10][maxW + 10];
chr c[maxH + 10][maxW + 10];

int main() {
    std::cin >> H >> W;
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) std::cin >> a[i][j];
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) b[i][j] = '.';
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) c[i][j] = '.';
    for (int i = 1; i <= H; i++) b[i][1] = '#';
    for (int i = 1; i <= H; i++) c[i][W] = '#';
    for (int i = 1; i <= H; i++) if (i & 1) for (int j = 1; j < W; j++) b[i][j] = '#'; else for (int j = W; j > 1; j--) c[i][j] = '#';
    for (int i = 1; i <= H; i++) if (i & 1) for (int j = 1; j <= W; j++) if (a[i][j] == '#') c[i][j] = '#'; else ; else for (int j = 1; j <= W; j++) if (a[i][j] == '#') b[i][j] = '#';
    for (int i = 1; i <= H; i++) {for (int j = 1; j <= W; j++) std::cout << b[i][j]; std::cout << '\n';} std::cout << '\n';
    for (int i = 1; i <= H; i++) {for (int j = 1; j <= W; j++) std::cout << c[i][j]; std::cout << '\n';}
    return 0;
}