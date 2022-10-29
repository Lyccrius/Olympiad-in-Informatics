#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

int n;
pii hand[1010];

bool cmp(pii a, pii b) {
    return a.first * a.second < b.first * b.second;
}

int main() {
    cin >> n;

    for (int i = 0; i <= n; i ++) {
        cin >> hand[i].first >> hand[i].second;
    }

    sort(hand + 1, hand + n + 1, cmp);

    int ans = 0;
    int mul = hand[0].first;

    for (int i = 1; i <= n; i ++) {
        ans = max(ans, mul / hand[i].second);
        mul *= hand[i].first;
    }

    cout << ans << endl;

    return 0;
}