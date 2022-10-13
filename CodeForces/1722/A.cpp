#include <bits/stdc++.h>

using namespace std;

char name[10] = "Timur";

int t;

int n;
char s[10];

int main() {
    sort(name, name + 5);

    scanf("%d", &t);
    
    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf(" %c", &s[i]);
        }

        sort(s, s + n);

        bool flag = true;

        for (int i = 0; i < n; i++) {
            if (n != 5 || s[i] != name[i]) {
                flag = false;
                printf("NO\n");
                break;
            }
        }

        if (flag) {
            printf("YES\n");
        }
    }

    return 0;
}