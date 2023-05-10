#include <bits/stdc++.h>

using namespace std;

map<pair<int, int>, bool> existed;

int N, P, H, M;
int A, B;

int C[100005], D[100005];

int main() {
    cin >> N >> P >> H >> M;

    while (M --) {
        cin >> A >> B;

        if (A > B) {
            swap(A, B);
        }

        if (existed[make_pair(A, B)]) {
            continue;
        }

        D[A + 1] --;
        D[B] ++;
        existed[make_pair(A, B)] = true;
    }

    for (int i = 1; i <= N; i ++) {
        C[i] = C[i - 1] + D[i];
        cout << C[i] + H << endl;
    }

    return 0;
}