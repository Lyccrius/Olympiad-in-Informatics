#include <cstdio>

const int maxN = 1e5;

int t;

int n;
char s[maxN + 10];

void mian() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    bool L = false;
    bool R = false;
    for (int i = 1; i <= n; i++) {
        if (s[i] == 'L') L = true;
        if (s[i] == 'R') R = true;
    }
    if (L == false || R == false) {
        printf("%d\n", -1);
        return;
    }
    int firstR = n + 1;
    int lastL = 0;
    for (int i = 1; i <= n; i++) if (s[i] == 'L') lastL = i;
    for (int i = n; i >= 1; i--) if (s[i] == 'R') firstR = i;
    if (lastL > firstR) {
        printf("%d\n", 0);
        return;
    }
    for (int i = 1; i < n; i++) if (s[i] != s[i + 1]) {
        printf("%d\n", i);
        return;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) mian();
    return 0;
}