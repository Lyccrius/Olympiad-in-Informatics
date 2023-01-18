#include <iostream>
#include <algorithm>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef std::vector<int> svi;

const int inf = 2147483647;
const int maxN = 5e4;
const int maxM = 5e4;
const int logN = 16;
const int logA = 27;

int n, m;
int a[maxN + 10];
int opt[maxM + 10];
int l[maxM + 10], r[maxM + 10];
int pos[maxM + 10];
int k[maxM + 10];

svi range;
int tot;

struct BinaryIndexedTree {
    struct SegmentTree {
        struct Node {
            int l, r;
            int lson;
            int rson;
            int val;
        } node[(maxN + maxM) * (logN * 2) * (logN * 2) + 10];

        int ncnt;
        int root[maxN + 10];

        void PushUp(int u) {
            node[u].val = node[node[u].lson].val + node[node[u].rson].val;
            //printf("node[%d] = node[%d] + node[%d] = %d\n", u, node[u].lson, node[u].rson, node[u].val);
            return;
        }

        void Build(int &u) {
            u = ++ncnt;
            return;
        }

        void Clone(int &u, int v) {
            u = ++ncnt;
            node[u] = node[v];
            return;
        }

        void Modify(int &u, int l, int r, int pos, int val) {
            if (u == 0) Build(u);
            //printf("-Modify node[%d] [%d, %d], %d, %d\n", u, l, r, pos, val);
            if (l == r) {
                node[u].val += val;
                return;
            }
            int mid = (l + r) / 2;
            if (pos <= mid) Modify(node[u].lson, l, mid, pos, val);
            else Modify(node[u].rson, mid + 1, r, pos, val);
            PushUp(u);
            return;
        }

        int QueryRank(svi u, svi v, int l, int r, int k) {
            if (l == r) return 0;
            //printf("SGT.QueryRank(%d, %d, %d)\n", l, r, k);
            int mid = (l + r) / 2;
            int cnt = 0;
            if (k <= mid) {
                if (u.size()) for (int i = 0; i < u.size(); i++) u[i] = node[u[i]].lson;
                if (v.size()) for (int i = 0; i < v.size(); i++) v[i] = node[v[i]].lson;
                return QueryRank(u, v, l, mid, k);
            } else {
                if (u.size()) for (int i = 0; i < u.size(); i++) cnt -= node[node[u[i]].lson].val;
                if (v.size()) for (int i = 0; i < v.size(); i++) cnt += node[node[v[i]].lson].val;
                if (u.size()) for (int i = 0; i < u.size(); i++) u[i] = node[u[i]].rson;
                if (v.size()) for (int i = 0; i < v.size(); i++) v[i] = node[v[i]].rson;
                return cnt + QueryRank(u, v, mid + 1, r, k);
            }
        }

        int QueryKth(svi u, svi v, int l, int r, int k) {
            //printf("SGT.QueryKth [%d, %d], %d\n", l, r, k);
            if (l == r) {
                //printf("break\n");
                return l;
            }
            int mid = (l + r) / 2;
            int cnt = 0;
            //printf("%d\n", cnt);
            //printf("?%d\n", node[v[0]].lson);
            for (int i = 0; i < u.size(); i++) cnt -= node[node[u[i]].lson].val;
            for (int i = 0; i < v.size(); i++) cnt += node[node[v[i]].lson].val;
            //printf("%d\n", cnt);
            if (k <= cnt) {
                //printf("Turn Left\n");
                for (int i = 0; i < u.size(); i++) u[i] = node[u[i]].lson;
                for (int i = 0; i < v.size(); i++) v[i] = node[v[i]].lson;
                return QueryKth(u, v, l, mid, k);
            } else {
                //printf("Turn Right\n");
                for (int i = 0; i < u.size(); i++) u[i] = node[u[i]].rson;
                for (int i = 0; i < v.size(); i++) v[i] = node[v[i]].rson;
                return QueryKth(u, v, mid + 1, r, k - cnt);
            }
        }
    } SGT;

    int LowBit(int val) {
        return val & -val;
    }

    void Add(int pos, int val) {
        //printf("BIT.Add(%d, %d)\n", pos, val);
        for (int i = pos; i <= n; i += LowBit(i)) {
            //printf("*** %d\n", i);
            SGT.Modify(SGT.root[i], 1, range.size() - 2, a[pos], val);
        }
        return;
    }

    int AskRank(int l, int r, int k) {
        svi u;
        svi v;
        l -= 1;
        while (l) {
            u.push_back(SGT.root[l]);
            l -= LowBit(l);
        }
        while (r) {
            v.push_back(SGT.root[r]);
            r -= LowBit(r);
        }
        return SGT.QueryRank(u, v, 1, range.size() - 2, k) + 1;
    }

    int AskKth(int l, int r, int k) {
        //printf("BIT.AskKth(%d, %d, %d)\n", l, r, k);
        svi u;
        svi v;
        l -= 1;
        while (l) {
            u.push_back(SGT.root[l]);
            l -= LowBit(l);
        }
        while (r) {
            v.push_back(SGT.root[r]);
            //printf("##### %d\n", SGT.root[r]);
            r -= LowBit(r);
        }
        //printf("%d %d\n", u.size(), v.size());
        return SGT.QueryKth(u, v, 1, range.size() - 2, k);
    }

    int AskPre(int l, int r, int k) {
        int rank = AskRank(l, r, k);
        if (rank == 1) return 0;
        return AskKth(l, r, rank - 1);
    }

    int AskSuf(int l, int r, int k) {
        //printf("BIT.AskSuf(%d, %d, %d)\n", l, r, k);
        if (k >= range.size() - 1) return range.size() - 1;
        int rank = AskRank(l, r, k + 1);
        //printf("rank = %d\n", rank);
        if (rank > r - l + 1) return range.size() - 1;
        return AskKth(l, r, rank);
    }
} BIT;

int main() {
    promote();
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) range.push_back(a[i]);
    for (int i = 1; i <= m; i++) {
        std::cin >> opt[i];
        if (opt[i] == 1) std::cin >> l[i] >> r[i] >> k[i];
        if (opt[i] == 2) std::cin >> l[i] >> r[i] >> k[i];
        if (opt[i] == 3) std::cin >> pos[i] >> k[i], range.push_back(k[i]);
        if (opt[i] == 4) std::cin >> l[i] >> r[i] >> k[i], range.push_back(k[i]);
        if (opt[i] == 5) std::cin >> l[i] >> r[i] >> k[i], range.push_back(k[i]);
    }
    range.push_back(-inf);
    range.push_back(inf);
    std::sort(range.begin(), range.end());
    tot = std::unique(range.begin(), range.end()) - range.begin();
    while (range.size() > tot) range.pop_back();
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(range.begin(), range.end(), a[i]) - range.begin();
    //printf("Discreted\n");
    //for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    //printf("\n");
    for (int i = 1; i <= n; i++) BIT.Add(i, 1);
    for (int i = 1; i <= m; i++) {
        //printf("----------\n");
        //printf("%d %d %d %d %d\n", opt[i], l[i], r[i], pos[i], k[i]);
        if (opt[i] == 1) {
            k[i] = std::lower_bound(range.begin(), range.end(), k[i]) - range.begin();
            std::cout << BIT.AskRank(l[i], r[i], k[i]) << '\n';
        }
        if (opt[i] == 2) {
            std::cout << range[BIT.AskKth(l[i], r[i], k[i])] << '\n';
        }
        if (opt[i] == 3) {
            BIT.Add(pos[i], -1);
            a[pos[i]] = std::lower_bound(range.begin(), range.end(), k[i]) - range.begin();
            BIT.Add(pos[i], 1);
        }
        if (opt[i] == 4) {
            k[i] = std::lower_bound(range.begin(), range.end(), k[i]) - range.begin();
            std::cout << range[BIT.AskPre(l[i], r[i], k[i])] << '\n';
        }
        if (opt[i] == 5) {
            k[i] = std::lower_bound(range.begin(), range.end(), k[i]) - range.begin();
            std::cout << range[BIT.AskSuf(l[i], r[i], k[i])] << '\n';
        }
    }
    return 0;
}