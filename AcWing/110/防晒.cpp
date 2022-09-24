#include <bits/stdc++.h>

using namespace std;

int C, L;

struct Cow{
    int minSPF;
    int maxSPF;

    bool operator < (const Cow &x) const {
        return minSPF > x.minSPF;
    }
}cow[2510];

struct Cream{
    int SPF;
    int cover;

    bool operator < (const Cream &x) const {
        return SPF > x.SPF;
    }
}cre[2510];

int ans = 0;

int main() {
    cin >> C >> L;

    for (int i = 0; i < C; i ++) {
        cin >> cow[i].minSPF >> cow[i].maxSPF;
    }

    for (int i = 0; i < L; i ++) {
        cin >> cre[i].SPF >> cre[i].cover;
    }

    sort(cow, cow + C);

    sort(cre, cre + L);

    for (int i = 0; i < C; i ++) {
        for (int j = 0; j < L; j ++) {
            if (cow[i].maxSPF < cre[j].SPF) {
                continue;
            }

            if (cow[i].minSPF > cre[j].SPF) {
                break;
            }

            if (cre[j].cover) {
                ans ++;
                cre[j].cover --;
                break;
            }
        }
    }

    cout << ans << endl;

    return 0;
}