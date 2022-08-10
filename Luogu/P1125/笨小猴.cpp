#include <bits/stdc++.h>

using namespace std;

char word[110];

bool vis[30];

int cnt[30];

bool check(int x) {
    if (x < 2) return false;

    for (int i = 2; i * i <= x; i ++) if (!(x % i)) return false;
    
    return true;
}

int main() {
    cin >> word;

    for (int i = 0; word[i] != '\0'; i ++) {
        int x = word[i] - 'a';

        vis[x] = true;
        cnt[x] ++;
    }

    int maxn = 0, minn = 110;

    for (int i = 0; i < 26; i ++) {
        if (vis[i]) {
            maxn = max(maxn, cnt[i]);
            minn = min(minn, cnt[i]);
        }
    }

    int dif = maxn - minn;

    if (check(dif)){
        cout << "Lucky Word" << endl;
        cout << dif << endl;
    } else {
        cout << "No Answer" << endl;
        cout << 0 << endl;
    }

    return 0;
}