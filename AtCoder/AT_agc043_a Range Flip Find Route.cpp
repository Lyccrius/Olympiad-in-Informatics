#include <iostream>

typedef char chr;

const int maxH = 100;
const int maxW = 100;

int H, W;
chr s[maxH + 10][maxW + 10];
int f[maxH + 10][maxW + 10];

int main() {
    std::cin >> H >> W;
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) std::cin >> s[i][j];
    f[1][1] = (s[1][1] == '#');
    for (int i = 2; i <= H; i++) f[i][1] = f[i - 1][1] + (s[i - 1][1] == '.' && s[i][1] == '#');
    for (int j = 2; j <= W; j++) f[1][j] = f[1][j - 1] + (s[1][j - 1] == '.' && s[1][j] == '#');
    for (int i = 2; i <= H; i++) for (int j = 2; j <= W; j++) f[i][j] = std::min(f[i - 1][j] + (s[i - 1][j] == '.' && s[i][j] == '#'), f[i][j - 1] + (s[i][j - 1] == '.' && s[i][j] == '#'));
    std::cout << f[H][W];
    return 0;
}