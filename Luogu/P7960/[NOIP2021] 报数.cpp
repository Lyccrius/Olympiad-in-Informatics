#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e7 + 10;

int T;
int x;

bool num[maxn];
int ans[maxn];

bool check(int x) {
    while (x) {
        if (x % 10 == 7) {
            return true;
        }

        x /= 10;
    }

    return false;
}

void multi(int x) {
    for (int i = x; i <= maxn; i += x) {
        num[i] = true;
    }
}

int main() {
    int last;

    for (int i = 1; i <= maxn; i++) {
        if (num[i]) {
            continue;
        }

        if (check(i)) {
            multi(i);
            continue;
        }

        ans[last] = i;
        last = i;
    }

    scanf("%d", &T);

    while (T--) {
        scanf("%d", &x);

        if (num[x]) {
            printf("-1\n");
        } else {
            printf("%d\n", ans[x]);
        }
    }

    return 0;
}