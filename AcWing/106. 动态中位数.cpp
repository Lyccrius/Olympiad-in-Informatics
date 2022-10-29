#include <bits/stdc++.h>

using namespace std;

int P;
int id, M;

int main() {
    cin >> P;

    while (P --) {
        cin >> id >> M;

        cout << id << " " << ((M + 1) >> 1) << endl;

        priority_queue<int> down;
        priority_queue<int, vector<int>, greater<int> > up;

        int cnt = 0;
        int x;

        for (int i = 1; i <= M; i ++) {
            cin >> x;

            if (down.empty() || x <= down.top()) {
                down.push(x);
            } else {
                up.push(x);
            }

            if (down.size() > up.size() + 1) {
                up.push(down.top());
                down.pop();
            }

            if (up.size() > down.size()) {
                down.push(up.top());
                up.pop();
            }

            if (i & 1) {
                cout << down.top() << " ";
                
                if (!((++ cnt) % 10)) {
                    cout << endl;
                }
            }
        }

        if (cnt % 10) {
            cout << endl;
        }
    }

    return 0;
}