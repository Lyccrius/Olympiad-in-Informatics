#include <cstdio>

int t;
char str[5];

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%s", str);
        if ((str[0] == 'Y' || str[0] == 'y') && (str[1] == 'E' || str[1] == 'e') && (str[2] == 'S' || str[2] == 's')) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}