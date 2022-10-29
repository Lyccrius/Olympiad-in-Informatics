#include <bits/stdc++.h>

using namespace std;

const int maxn = 1000 + 10;

typedef pair<string, int> psi;
typedef map<string, int> msi;

int n, m = -1e9;
psi _round[maxn];

msi total;
msi _total;
string winner;

int main() {
    scanf("%d", &n);

    string name;
    int score;

    for (int i = 1; i <= n; i++){
        cin >> name >> score;
        
        _round[i].first = name;
        _round[i].second = score;
        total[name] += score;
    }

    for (int i = 1; i <= n; i++) {
        m = max(m, total[_round[i].first]);
    }

    for (int i = 1; i <= n; i++) {
        _total[_round[i].first] += _round[i].second;

        if (_total[_round[i].first] >= m && total[_round[i].first] == m) {
            cout << _round[i].first << endl;

            return 0;
        }
    }

    return 0;
}