#include <bits/stdc++.h>

using namespace std;

int N, F;
double a[100001], b[100001], sum[100001];

int main() {
    cin >> N >> F;

    for (int i = 1; i <= N; i ++) {
        cin >> a[i];
    }

    double eps = 1e-5;
    double l = -1e6, r = 1e6;

    while (r - l > eps) {
        double mid = (l + r) / 2;

        for (int i = 1; i <= N; i ++) {
            b[i] = a[i] - mid;
        }

        for (int i = 1; i <= N; i ++) {
            sum[i] = (sum[i - 1] + b[i]);
        }
            
        double ans = -1e10;
        double min_val = 1e10;

        for (int i = F; i <= N; i ++) {
            min_val = min(min_val, sum[i - F]);
            ans = max(ans, sum[i] - min_val);
        }

        if (ans >= 0) {
            l = mid;
        } else {
            r = mid;
        }
    }

    cout << int(r * 1000) << endl;

    return 0;
}