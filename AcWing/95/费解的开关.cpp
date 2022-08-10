#include <bits/stdc++.h>

using namespace std;

int n;

char origin[10][10];
char matrix[10][10];

void turn(int x, int y) {
    matrix[x][y] ^= 1;
    matrix[x-1][y] ^= 1;
    matrix[x+1][y] ^= 1;
    matrix[x][y-1] ^= 1;
    matrix[x][y+1] ^= 1;

    return;
}

int main() {
    cin >> n;

    while (n --) {
        for (int i = 0; i < 5; i ++) cin >> origin[i];

        int ans = 0x7f7f7f7f;
        int opt = 16;
        for (int opt = 0; opt < (1 << 5); opt ++) {
            int step = 0;

            memcpy(matrix, origin, sizeof(origin));

            for (int i = 0; i < 5; i ++) {
                if ((opt >> i) & 1) {
                    step ++;

                    turn(0, i);
                }
            }

            for (int i = 0; i < 4; i ++) {
                for (int j = 0; j < 5; j ++) {
                    if (matrix[i][j] == '0') {
                        step ++;

                        turn(i + 1, j);
                    }
                }
            }

            bool check = true;

            for (int i = 0; i < 5; i ++) {
                if (matrix[4][i] == '0') {
                    check = false;
                    break;
                }
            }

            if (check) {
                ans = min(ans, step);
            }
        }

        cout << ((ans <= 6) ? ans : -1) << endl;
    }

    return 0;
}