#include <bits/stdc++.h>

using namespace std;

int C, L;

pair<int, int>cow[2505];
pair<int, int>cre[2505];

bool cmp(pair<int, int> a, pair<int, int> b) {
    return a.first > b.first;
}

int ans = 0;

int main() {
    cin >> C >> L;

    for (int i = 1; i <= C; i ++) {
        cin >> cow[i].first >> cow[i].second;
    }

    for (int i = 1; i <= L; i ++) {
        cin >> cre[i].first >> cre[i].second;
    }

    sort(cow + 1, cow + C + 1, cmp);

    sort(cre + 1, cre + L + 1, cmp);

    for (int i = 1; i <= C; i ++) {
        for (int j = 1; j <= L; j ++) {
            if (cow[i].second < cre[j].first) {
                continue;
            }

            if (cow[i].first > cre[j].first) {
                break;
            }

            if (cre[j].second) {
                ans ++;
                cre[j].second --;
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}