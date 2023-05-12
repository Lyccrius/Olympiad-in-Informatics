#include <iostream>

int n;
int a[10][10];
int b[10][10];
int c[10][10];
int t[10][10];
int row1;
int row2;
int row3;
int col1;
int col2;
int col3;
int segr;
int segc;

void generate() {
    for (int i = 1; i <= 9; i++) for (int j = 1; j <= 9; j++) c[i][j] = b[i][j];
    switch (row1) {
        case 1: {
            break;
        }
        case 2: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[2][j], c[3][j]);
            }
            break;
        }
        case 3: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[1][j], c[2][j]);
            }
            break;
        }
        case 4: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[1][j], c[2][j]);
                std::swap(c[2][j], c[3][j]);
            }
            break;
        }
        case 5: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[1][j], c[3][j]);
                std::swap(c[2][j], c[3][j]);
            }
            break;
        }
        case 6: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[1][j], c[3][j]);
            }
        }
    }
    switch (row2) {
        case 1: {
            break;
        }
        case 2: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[5][j], c[6][j]);
            }
            break;
        }
        case 3: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[4][j], c[5][j]);
            }
            break;
        }
        case 4: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[4][j], c[5][j]);
                std::swap(c[5][j], c[6][j]);
            }
            break;
        }
        case 5: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[4][j], c[6][j]);
                std::swap(c[5][j], c[6][j]);
            }
            break;
        }
        case 6: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[4][j], c[6][j]);
            }
        }
    }
    switch (row3) {
        case 1: {
            break;
        }
        case 2: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[8][j], c[9][j]);
            }
            break;
        }
        case 3: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[7][j], c[8][j]);
            }
            break;
        }
        case 4: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[7][j], c[8][j]);
                std::swap(c[8][j], c[9][j]);
            }
            break;
        }
        case 5: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[7][j], c[9][j]);
                std::swap(c[8][j], c[9][j]);
            }
            break;
        }
        case 6: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[7][j], c[9][j]);
            }
        }
    }
    switch (col1) {
        case 1: {
            break;
        }
        case 2: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][2], c[j][3]);
            }
            break;
        }
        case 3: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][1], c[j][2]);
            }
            break;
        }
        case 4: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][1], c[j][2]);
                std::swap(c[j][2], c[j][3]);
            }
            break;
        }
        case 5: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][1], c[j][3]);
                std::swap(c[j][2], c[j][3]);
            }
            break;
        }
        case 6: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][1], c[j][3]);
            }
        }
    }
    switch (col2) {
        case 1: {
            break;
        }
        case 2: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][5], c[j][6]);
            }
            break;
        }
        case 3: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][4], c[j][5]);
            }
            break;
        }
        case 4: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][4], c[j][5]);
                std::swap(c[j][5], c[j][6]);
            }
            break;
        }
        case 5: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][4], c[j][6]);
                std::swap(c[j][5], c[j][6]);
            }
            break;
        }
        case 6: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][4], c[j][6]);
            }
        }
    }
    switch (col3) {
        case 1: {
            break;
        }
        case 2: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][8], c[j][9]);
            }
            break;
        }
        case 3: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][7], c[j][8]);
            }
            break;
        }
        case 4: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][7], c[j][8]);
                std::swap(c[j][8], c[j][9]);
            }
            break;
        }
        case 5: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][7], c[j][9]);
                std::swap(c[j][8], c[j][9]);
            }
            break;
        }
        case 6: {
            for (int j = 1; j <= 9; j++) {
                std::swap(c[j][7], c[j][9]);
            }
        }
    }
    switch (segr) {
        case 1: {
            break;
        }
        case 2: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[3 + i][j], c[6 + i][j]);
                }
            }
            break;
        }
        case 3: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[i][j], c[3 + i][j]);
                }
            }
            break;
        }
        case 4: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[i][j], c[3 + i][j]);
                    std::swap(c[3 + i][j], c[6 + i][j]);
                }
            }
            break;
        }
        case 5: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[i][j], c[6 + i][j]);
                }
            }
            break;
        }
        case 6: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[i][j], c[6 + i][j]);
                    std::swap(c[3 + i][j], c[6 + i][j]);
                }
            }
            break;
        }
    }
    switch (segc) {
        case 1: {
            break;
        }
        case 2: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[j][3 + i], c[j][6 + i]);
                }
            }
            break;
        }
        case 3: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[j][i], c[j][3 + i]);
                }
            }
            break;
        }
        case 4: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[j][i], c[j][3 + i]);
                    std::swap(c[j][3 + i], c[j][6 + i]);
                }
            }
            break;
        }
        case 5: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[j][i], c[j][6 + i]);
                }
            }
            break;
        }
        case 6: {
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 9; j++) {
                    std::swap(c[j][i], c[j][6 + i]);
                    std::swap(c[j][3 + i], c[j][6 + i]);
                }
            }
            break;
        }
    }
    return;
}

bool check() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            if (c[i][j] == 0) continue;
            if (a[i][j] != c[i][j]) return false;
        }
    }
    return true;
}

void rotate() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            t[i][j] = c[9 - j + 1][i];
        }
    }
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            c[i][j] = t[i][j];
        }
    }
    return;
}

void show() {
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            std::cout << c[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return;
}

void mian() {
    for (int i = 1; i <= 9; i++) for (int j = 1; j <= 9; j++) scanf("%1d", &a[i][j]);
    for (int i = 1; i <= 9; i++) for (int j = 1; j <= 9; j++) scanf("%1d", &b[i][j]);
    for (row1 = 1; row1 <= 6; row1++) {
        for (row2 = 1; row2 <= 6; row3++) {
            for (row3 = 1; row3 <= 6; row3++) {
                for (col1 = 1; col1 <= 6; col1++) {
                    for (col2 = 1; col2 <= 6; col2++) {
                        for (col3 = 1; col3 <= 6; col3++) {
                            for (segr = 1; segr <= 6; segr++) {
                                for (segc = 1; segc <= 6; segc++) {
                                    generate();
                                    for (int i = 1; i <= 4; i++) {
                                        //show();
                                        if (check()) {
                                            std::cout << "Yes" << '\n';
                                            return;
                                        }
                                        rotate();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << "No" << '\n';
    return;
}

int main() {
    std::cin >> n;
    while (n--) mian();
    return 0;
}