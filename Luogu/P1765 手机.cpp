#include <cstdio>

int table[30] = {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1, 2, 3, 4};
char ch;
int cnt;

int main() {
    while (scanf("%c", &ch) != EOF) {
        if (ch >= 'a' && ch <= 'z') cnt += table[ch - 'a'];
        if (ch == ' ') cnt++;
    }
    printf("%d\n", cnt);
    return 0;
}