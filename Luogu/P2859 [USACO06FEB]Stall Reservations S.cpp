#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, int> ppi;

int N;
ppi cow[500005];

int cnt = 0;
int res[500005];
int bak[500005];

bool cmp(ppi a, ppi b) {
    return a.first.first < b.first.first;
}

int main() {
    cin >> N;

    for (int i = 1; i <= N; i ++) {
        cin >> cow[i].first.first >> cow[i].first.second;
        cow[i].second = i;
    }

    sort(cow + 1, cow + N + 1, cmp);

    priority_queue<pii, vector<pii>, greater<pii> > wait;
    priority_queue<int, vector<int>, greater<int> > free;

    for (int i = 1; i <= N; i ++) {
        while (!wait.empty() && wait.top().first < cow[i].first.first) {
            free.push(wait.top().second);
            wait.pop();
        }

        if (free.empty()) {
            free.push(++ cnt);
        }

        res[cow[i].second] = free.top();
        free.pop();

        wait.push(make_pair(cow[i].first.second, res[cow[i].second]));
    }

    cout << cnt << endl;

    for (int i = 1; i <= N; i ++) {
        cout << res[i] << endl;
    }

    return 0;
}