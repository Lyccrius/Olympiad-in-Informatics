#include <bits/stdc++.h>

using namespace std;

int N, M, T;
int x, y;

long long row[100010];
long long col[100010];
long long sum;

char res[5][20] = {
    "impossible",
    "column",
    "row",
    "both"
};

int flag;
long long ans;

void calc(long long line[], int len) {
    flag *= 2;

    if (sum % len) {
        return;
    }

    int pur = sum / len;
    int pre[100010];

    for (int i = 1; i <= len; i ++) {
        pre[i] = pre[i - 1] + line[i] - pur;
    }

    sort(pre + 1, pre + 1 + len);

    int k = (len + 1) >> 1;
    int cnt = 0;

    for (int i = 1; i <= len; i ++) {
        cnt += abs(pre[i] - pre[k]);
    }

    ans += cnt;
    flag ++;

    return;
}

int main() {
    cin >> N >> M >> T;

    while (T --) {
        cin >> x >> y;

        row[x] ++;
        col[y] ++;
        sum ++;
    }

    calc(row, N);
    calc(col, M);

    cout << res[flag] << " ";
    
    if (flag) {
        cout << ans << endl;
    }

    return 0;
}