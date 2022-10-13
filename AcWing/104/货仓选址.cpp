#include <bits/stdc++.h>

using namespace std;

int N;
int A[100010];

int main() {
    cin >> N;

    for (int i = 1; i <= N; i ++) {
        cin >> A[i];
    }

    sort (A + 1, A + N + 1);

    int pos = A[(N + 1) / 2];
    int ans = 0;

    for (int i = 1; i <= N; i ++) {
        ans += abs(pos - A[i]);
    }

    cout << ans << endl;

    return 0;
}