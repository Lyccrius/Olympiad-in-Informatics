#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int handle[10][10];

int N;
queue<pii> ans;

int main() {
    memset(handle, 0, sizeof(handle));

    char x;

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            scanf(" %c", &x);

            if (x == '+') {
                handle[i][j] = 1;
                handle[i][0]++;
                handle[0][j]++;
            } else {
                handle[i][j] = 0;
            }
        }
    }

    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            if ((handle[i][0] + handle[0][j] - handle[i][j]) & 1) {
                N++;
                ans.push(make_pair(i, j));
            }
        }
    }

    printf("%d\n", N);

    while (!ans.empty()) {
        pii t = ans.front();
        ans.pop();
        printf("%d %d\n", t.first, t.second);
    }

    return 0;
}