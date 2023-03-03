#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 133333;
const int maxM = 133333;
const int maxA = 1e6;
const int sqrtN = 2610;

int N, M;
int A[maxN + 10];
char op;
int L, R;
int P, Col;

struct CaptainMo {
    struct Query {
        int i;
        int l, r;
        int t;
        int lbel;
        int rbel;

        bool operator<(const Query &other) const {
            if (lbel != other.lbel) return lbel < other.lbel;
            if (rbel != other.rbel) return rbel < other.rbel;
            return t < other.t;
        }
    };

    struct Modify {
        int pos;
        int val;
    };

    std::vector<Query> q;
    std::vector<Modify> m;

    void Init() {
        std::sort(q.begin(), q.end());
        return;
    }

    int res;
    int cnt[maxA + 10];
    int ans[maxM + 10];

    void Add(int val) {
        if (cnt[val] == 0) res++;
        cnt[val]++;
        return;
    }

    void Del(int val) {
        cnt[val]--;
        if (cnt[val] == 0) res--;
        return;
    }

    void Move(int i, int t) {
        if (q[i].l <= m[t].pos && m[t].pos <= q[i].r) {
            Del(A[m[t].pos]);
            Add(m[t].val);
        }
        std::swap(A[m[t].pos], m[t].val);
        return;
    }

    void Solve() {
        int l = 1;
        int r = 0;
        int t = - 1;
        for (int i = 0; i < q.size(); i++) {
            while (l < q[i].l) Del(A[l]), l++;
            while (l > q[i].l) l--, Add(A[l]);
            while (r < q[i].r) r++, Add(A[r]);
            while (r > q[i].r) Del(A[r]), r--;
            while (t < q[i].t) ++t, Move(i, t);
            while (t > q[i].t) Move(i, t), t--;
            ans[q[i].i] = res;
        }
        return;
    }

    void Show() {
        for (int i = 0; i < q.size(); i++) std::cout << ans[i] << '\n';
        return;
    }
} CMO;

int main() {
    promote();
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++) std::cin >> A[i];
    for (int i = 1; i <= M; i++) {
        std::cin >> op;
        if (op == 'Q') {
            std::cin >> L >> R;
            CaptainMo::Query query;
            query.l = L;
            query.r = R;
            query.i = CMO.q.size();
            query.t = CMO.m.size() - 1;
            query.lbel = (L - 1) / sqrtN + 1;
            query.rbel = (R - 1) / sqrtN + 1;
            CMO.q.push_back(query);
        } else if (op == 'R') {
            std::cin >> P >> Col;
            CaptainMo::Modify modify;
            modify.pos = P;
            modify.val = Col;
            CMO.m.push_back(modify);
        }
    }
    CMO.Init();
    CMO.Solve();
    CMO.Show();
    return 0;
}