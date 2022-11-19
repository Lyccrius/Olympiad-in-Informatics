#include <cstdio>

const int maxN = 80 + 10;

int n, L;
int cnt;
int s[maxN];

int DFS(int cur) {
    if(cnt++ == n) {
        for(int i = 0; i < cur; i++) {
            if(i % 64 == 0 && i > 0) printf("\n");
            else if(i % 4 == 0 && i > 0) printf(" ");
            printf("%c", 'A' + s[i]);
        }
        printf("\n%d\n", cur);
        return 0;
    }
    for (int i = 0; i < L; i++) {
        s[cur] = i;
        bool ok = true;
        for (int j = 1; j * 2 <= cur + 1; j++) {
            bool equal = true;
            for (int k = 0; k < j; k++) if (s[cur - k] != s[cur - k - j]) {
                equal = false;
                break;
            }
            if (equal) {
                ok = false;
                break;
            }
        }
        if (ok) if (!DFS(cur + 1)) return 0;
    }
    return 1;
}

int main() {
    while (scanf("%d%d", &n, &L) == 2 && n) {
        cnt = 0;
        DFS(0);
    }
    return 0;
}