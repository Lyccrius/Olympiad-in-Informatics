#include <iostream>
#include <algorithm>
#include <deque>

const int maxN = 5e4;
const int maxM = 5e4;
const int maxK = 5e4;

const int sqrtN = 223;

int n, m, k;
int l, r;
int a[maxN + 10];
int b[maxN + 10];
int c[maxK + 10];
int ans[maxM + 10];
int res;

struct CaptainMo {
    struct Query {
        int i;
        int l, r;

        bool operator<(const Query &other) const {
            if (b[l] != b[other.l]) return b[l] < b[other.l];
            return r < other.r;
        }
    };

    std::deque<Query> querys;

    void Init() {
        std::sort(querys.begin(), querys.end());
        return;
    }

    void Add(int p) {
        c[a[p]]++;
        res += 2 * c[a[p]] - 1;
        return;
    }

    void Del(int p) {
        res -= 2 * c[a[p]] - 1;
        c[a[p]]--;
        return;
    }

    void Solve() {
        int l = 1;
        int r = 0;
        for (auto query : querys) {
            while (l > query.l) Add(--l);
            while (r < query.r) Add(++r);
            while (l < query.l) Del(l++);
            while (r > query.r) Del(r--);
            ans[query.i] = res;
        }
        return;
    }

    void Show() {
        for (int i = 1; i <= m; i++) std::cout << ans[i] << '\n';
        return;
    }
} CMO;

int main() {
    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) b[i] = (i - 1) / sqrtN + 1;
    for (int i = 1; i <= m; i++) std::cin >> l >> r, CMO.querys.push_back((CaptainMo::Query) {i, l, r});
    CMO.Init();
    CMO.Solve();
    CMO.Show();
    return 0;
}