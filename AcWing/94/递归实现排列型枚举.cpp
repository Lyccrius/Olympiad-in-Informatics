#include <bits/stdc++.h>

using namespace std;

int n;

int order[20];

bool chosen[20];

void calc(int k) {
    if (k == n + 1) {
        for (int i = 1; i <= n; i ++) cout << order[i] << " ";

        cout << endl;

        return;
    }

    for (int i = 1; i <= n; i ++) {
        if (chosen[i]) continue;

        order[k] = i;
        chosen[i] = true;

        calc(k + 1);

        chosen[i] = false;
    }

    return;
}

int main() {
    cin >> n;

    calc(1);

    return 0;
}