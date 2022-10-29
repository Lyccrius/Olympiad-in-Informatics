#include <bits/stdc++.h>

using namespace std;

const int maxn = 2e6 + 10;

int n;
char pos[maxn];

bool check() {
    int cnt = 0;
    int len = strlen(pos);

    while (pos[++cnt] >= 'A' && cnt <= len);

    while (pos[++cnt] <= '9' && cnt <= len);

    if (cnt >= len) {
        return true;
    } else {
        return false;
    }
}


void Excel2RC() {
    int x = 0, y = 0;

    int cnt = 0;

    while (pos[cnt] >= 'A') {
        y = y * 26 + (pos[cnt++] - 'A' + 1);
    }

    while (pos[cnt] != '\0') {
        x = x * 10 + (pos[cnt++] - '0');
    }

    printf("R%dC%d\n", x, y);

    return;
}

void RC2Excel() {
    int x = 0, y = 0;

    int cnt = 0;

    while (pos[++cnt] != 'C') {
        x = x * 10 + (pos[cnt] - '0');
    }

    while (pos[++cnt] != '\0') {
        y = y * 10 + (pos[cnt] - '0');
    }

    char t[maxn];
    int tot = 0;

    while (y) {
        if (y % 26) {
            t[tot++] = y % 26 + 'A' - 1;
            y = y / 26;
        } else {
            t[tot++] = 'Z';
            y = y / 26 - 1;
        }
    }

    while (tot--) {
        printf("%c", t[tot]);
    }

    printf("%d\n", x);

    return;
}

int main() {
    scanf("%d", &n);

    while (n --) {
        scanf("%s", pos);

        if (check()) {
            Excel2RC();
        } else {
            RC2Excel();
        }
    }

    return 0;
}