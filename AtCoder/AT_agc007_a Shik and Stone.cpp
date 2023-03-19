#include <iostream>

typedef char chr;

const int maxH = 8;
const int maxW = 8;

int H, W;
chr a[maxH + 10][maxW + 10];
int l[maxH + 10];
int r[maxH + 10];

int main() {
    std::cin >> H >> W;
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) std::cin >> a[i][j];
    for (int i = 1; i <= H; i++) for (int j = 1; j <= W; j++) if (a[i][j] == '#') r[i] = j; //printf("r[%d] = %d\n", i, j);
    for (int i = 1; i <= H; i++) for (int j = W; j >= 1; j--) if (a[i][j] == '#') l[i] = j; //printf("l[%d] = %d\n", i, j);
    for (int i = 2; i <= H; i++) if (l[i] != r[i - 1]) {std::cout << "Impossible" << '\n'; return 0;}
    std::cout << "Possible" << '\n';
    return 0;
}