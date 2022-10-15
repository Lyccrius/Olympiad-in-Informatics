#include <cstdio>

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);
        char s[n];
        scanf("%s", s);

        int l = 0;
        int r = n - 1;
        
        while (s[l] == '0') {
            l++;
        }
        while (s[r] == '1') {
            r--;
        }

        if (l < r) {
            for (int i = 0; i < l; i++) {
                printf("%c", s[i]);
            }
            for (int i = r; i < n; i++) {
                printf("%c", s[i]);
            }
        } else {
            printf("%s", s);
        }

        printf("\n");
    }

    return 0;
}