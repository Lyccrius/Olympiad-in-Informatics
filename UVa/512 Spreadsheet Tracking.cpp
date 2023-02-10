#include <iostream>
#include <algorithm>

typedef std::pair<int, int> pii;

const int maxN = 50;
const int maxA = 10;

int kase;
int r, c;
int n;
char op[10];
int r1, c1, r2, c2;
int A;
int x[maxA + 10];
int q;
int cx[maxN + 10][maxN + 10];
int cy[maxN + 10][maxN + 10];
int ax[maxN + 10][maxN + 10];
int ay[maxN + 10][maxN + 10];

void init() {
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) cx[i][j] = i;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) cy[i][j] = j;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) ax[i][j] = 0;
    for (int i = 1; i <= r; i++) for (int j = 1; j <= c; j++) ay[i][j] = 0;
    return;
}

void EX() {
    std::cin >> r1 >> c1 >> r2 >> c2;
    std::swap(cx[r1][c1], cx[r2][c2]);
    std::swap(cy[r1][c1], cy[r2][c2]);
    return;
}

void DC() {
    std::cin >> A;
    for (int i = 1; i <= A; i++) std::cin >> x[i];
    std::sort(x + 1, x + A + 1);
    for (int k = 1; k <= A; k++) {
        for (int i = 1; i <= r; i++) {
            for (int j = x[k] - k + 1; j <= c - 1; j++) {
                cx[i][j] = cx[i][j + 1];
                cy[i][j] = cy[i][j + 1];
            }
        }
        for (int i = 1; i <= r; i++) {
            cx[i][c] = 0;
            cy[i][c] = 0;
        }
        c--;
    }
    return;
}

void DR() {
    std::cin >> A;
    for (int i = 1; i <= A; i++) std::cin >> x[i];
    std::sort(x + 1, x + A + 1);
    for (int k = 1; k <= A; k++) {
        for (int i = x[k] - k + 1; i <= r - 1; i++) {
            for (int j = 1; j <= c; j++) {
                cx[i][j] = cx[i + 1][j];
                cy[i][j] = cy[i + 1][j];
            }
        }
        for (int j = 1; j <= c; j++) {
            cx[r][j] = 0;
            cy[r][j] = 0;
        }
        r--;
    }
    return;
}

void IC() {
    std::cin >> A;
    for (int i = 1; i <= A; i++) std::cin >> x[i];
    std::sort(x + 1, x + A + 1);
    for (int k = 1; k <= A; k++) {
        for (int i = 1; i <= r; i++) {
            for (int j = c + 1; j >= x[k] + k; j--) {
                cx[i][j] = cx[i][j - 1];
                cy[i][j] = cy[i][j - 1];
            }
        }
        for (int i = 1; i <= r; i++) {
            cx[i][x[k] + k - 1] = 0;
            cy[i][x[k] + k - 1] = 0;
        }
        c++;
    }
    return;
}

void IR() {
    std::cin >> A;
    for (int i = 1; i <= A; i++) std::cin >> x[i];
    std::sort(x + 1, x + A + 1);
    for (int k = 1; k <= A; k++) {
        for (int i = r + 1; i >= x[k] + k; i--) {
            for (int j = 1; j <= c; j++) {
                cx[i][j] = cx[i - 1][j];
                cy[i][j] = cy[i - 1][j];
            }
        }
        for (int j = 1; j <= c; j++) {
            cx[x[k] + k - 1][j] = 0;
            cy[x[k] + k - 1][j] = 0;
        }
        r++;
    }
    return;
}

void show() {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            printf("(%d, %d) ", cx[i][j], cy[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void mian() {
    init();
    std::cin >> n;
    while (n--) {
        std::cin >> op;
        if (op[0] == 'E' && op[1] == 'X') EX();
        if (op[0] == 'D' && op[1] == 'C') DC();
        if (op[0] == 'D' && op[1] == 'R') DR();
        if (op[0] == 'I' && op[1] == 'C') IC();
        if (op[0] == 'I' && op[1] == 'R') IR();
        //show();
    }
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            ax[cx[i][j]][cy[i][j]] = i;
            ay[cx[i][j]][cy[i][j]] = j;
        }
    }
    if (kase) printf("\n");
    printf("Spreadsheet #%d\n", ++kase);
    std::cin >> q;
    while (q--) {
        std::cin >> r >> c;
        if (ax[r][c]) printf("Cell data in (%d,%d) moved to (%d,%d)\n", r, c, ax[r][c], ay[r][c]);
        else printf("Cell data in (%d,%d) GONE\n", r, c);
    }
    //printf("\n");
    return;
}

int main() {
    while (std::cin >> r >> c && r && c) mian();
    return 0;
}