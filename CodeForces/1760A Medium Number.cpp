#include <cstdio>

int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        char s[50];
        scanf("%s", s);
        switch(s[0]) {
            case 'Y': {
                char index[5] = "Yes";
                bool ok = true;
                for (int i = 0; s[i] != '\0'; i++) {
                    if (s[i] != index[i % 3]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) printf("YES\n");
                else printf("NO\n");
                break;
            }
            case 'e': {
                char index[5] = "esY";
                bool ok = true;
                for (int i = 0; s[i] != '\0'; i++) {
                    if (s[i] != index[i % 3]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) printf("YES\n");
                else printf("NO\n");
                break;
            }
            case 's': {
                char index[5] = "sYe";
                bool ok = true;
                for (int i = 0; s[i] != '\0'; i++) {
                    if (s[i] != index[i % 3]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) printf("YES\n");
                else printf("NO\n");
                break;
            }
            default: {
                printf("NO\n");
                break;
            }
        }
    }
    return 0;
}