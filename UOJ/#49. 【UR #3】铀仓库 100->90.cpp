#include <iostream>

#define int long long

typedef long long lxl;

const int maxN = 5e5;
const lxl maxT = 1e18;
const int maxA = 1e4;
const int maxX = 1e9;
const lxl sumA = 5e9;

int n;
lxl t;
int x[maxN + 10];
int a[maxN + 10];

bool check(lxl mid) {
    int l = 1;
    int r = 1;
    lxl cl = 0;
    lxl cr = 0;
    lxl cnt = a[1];
    lxl sum = 0;
    while (r < n && cnt < mid) {
        r++;
        cr += a[r];
        cnt += a[r];
        sum += a[r] * (x[r] - x[1]);
    }
    if (r == n && cnt < mid) return false;
    for (int s = 1; s <= n; s++) {
        while (r < n && x[r + 1] - x[s] < x[s] - x[l]) {
            r++;
            cr += a[r];
            cnt += a[r];
            sum += a[r] * (x[r] - x[s]);
            while (l < s && cnt - a[l] >= mid) {
                cl -= a[l];
                cnt -= a[l];
                sum -= a[l] * (x[s] - x[l]);
                l++;
            }
        }
        if (sum - (cnt - mid) * std::max(x[r] - x[s], x[s] - x[l]) <= t / 2) return true;
        cl += a[s];
        sum += cl * (x[s + 1] - x[s]);
        sum -= cr * (x[s + 1] - x[s]);
        cr -= a[s + 1];
    }
    return false;
}

signed main() {
    std::cin >> n >> t;
    for (int i = 1; i <= n; i++) std::cin >> x[i];
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    lxl l = 0;
    lxl r = sumA;
    while (l < r) {
        lxl mid = (l + r + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }
    std::cout << l << '\n';
    return 0;
}