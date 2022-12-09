#include <cstdio>
#include <cstring>
#include <algorithm>

char ch;
int cnt[30];
int maxT;

int main() {
    while (scanf("%c", &ch) != EOF) if (ch >= 'A' && ch <= 'Z') cnt[ch - 'A' + 1]++;
    for (int i = 1; i <= 26; i++) maxT = std::max(maxT, cnt[i]);
    for (int i = maxT; i > 0; i--) {
        for (int j = 1; j <= 26; j++) if (cnt[j] >= i) printf("* "); else printf("  ");
        printf("\n");
    }
    for (int i = 1; i <= 26; i++) printf("%c ", i + 'A' - 1);
    printf("\n");
    return 0;
}