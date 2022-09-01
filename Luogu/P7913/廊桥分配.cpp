#include <bits/stdc++.h>

using namespace std;

int n, m1, m2;

struct flight {
    int a;
    int b;

    friend istream& operator >> (istream &is, flight &x) {
        is >> x.a >> x.b;

        return is;
    }

    friend ostream& operator << (ostream &os, flight &x) {
        os << x.a << x.b;

        return os;
    }
}ins[100010], ots[100010];

struct cmpFunctor {
    bool operator () (flight &x, flight &y) {
        if (x.a != y.a) {
            return x.a < y.a;
        }

        return x.b < y.b;
    }
};

int resi[100010],  reso[100010];

typedef pair<int, int> pii;

void calc(flight fli[], int m, int res[]) {
    priority_queue<pii, vector<pii>, greater<pii> > wait;
    priority_queue<int, vector<int>, greater<int> > free;

    for (int i = 1; i <= n; i ++) {
        free.push(i);
    }

    for (int i = 1; i <= m; i ++) {
        while (!wait.empty() && fli[i].a >= wait.top().first) {
            free.push(wait.top().second);
            wait.pop();
        }

        if (free.empty()) {
            continue;
        }

        int dest = free.top();
        free.pop();

        res[dest] ++;
        wait.push(make_pair(fli[i].b, dest));
    }

    for (int i = 1; i <= n; i ++) {
        res[i] = res[i - 1] + res[i];
    }

    return;
}

int main(){
    cin >> n >> m1 >> m2;

    for (int i = 1; i <= m1; i ++) {
        cin >> ins[i];
    }

    for (int i = 1; i <= m2; i ++) {
        cin >> ots[i];
    }

    sort(ins + 1, ins + 1 + m1, cmpFunctor());
    sort(ots + 1, ots + 1 + m2, cmpFunctor());

    calc(ins, m1, resi);
    calc(ots, m2, reso);

    int ans = 0;

    for (int i = 0; i <= n; i ++) {
        ans = max(ans, resi[i] + reso[n - i]);
    }

    cout << ans << endl;

    return 0;
}