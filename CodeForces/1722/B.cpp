#include <bits/stdc++.h>

using namespace std;

int t;

int n;
bool str1[110];
bool str2[110];

int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        char x;

        for (int i = 0; i < n; i++) {
            scanf(" %c", &x);
            
            if (x == 'R') {
                str1[i] = true;
            } else {
                str1[i] = false;
            }
        }

        for (int i = 0; i < n; i++) {
            scanf(" %c", &x);
            
            if (x == 'R') {
                str2[i] = true;
            } else {
                str2[i] = false;
            }
        }

        bool flag = true;

        for (int i = 0; i < n; i++) {
            if (str1[i] ^ str2[i]) {
                printf("NO\n");
                flag = false;
                break;
            }
        }

        if (flag) {
            printf("YES\n");
        }
    }

    return 0;
}