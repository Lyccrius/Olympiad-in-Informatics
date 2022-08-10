#include <bits/stdc++.h>

using namespace std;

int n;

long long N, A, B;

pair<long long, long long> calc(long long N, long long M) {
    if (N == 0) return make_pair(0, 0);

    long long len = 1ll << (N - 1);
    long long cnt = 1ll << (2 * N - 2);

    pair<long long, long long> pos = calc(N - 1, M % cnt);

    long long x = pos.first;
    long long y = pos.second;
    long long z = M / cnt;

    if (z == 0) return make_pair(y, x);
    if (z == 1) return make_pair(x, y + len);
    if (z == 2) return make_pair(x + len, y + len);
    return make_pair(2 * len - y - 1, len - x - 1);
}

int main() {
    cin >> n;

    while (n --) {
        cin >> N >> A >> B;

        pair<long long, long long>a = calc(N, A - 1);
        pair<long long, long long>b = calc(N, B - 1);

        double x = a.first - b.first;
        double y = a.second - b.second;
        
        printf("%0.lf\n", sqrt(x * x + y * y) * 10);
    }

    return 0;
}