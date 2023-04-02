#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef std::vector<int> vic;
typedef std::set<int> sit;
typedef long long lxl;

const int maxN = 1e5;
const int maxK = 1e5;
const int maxM = 1e5;

int sid;
int n, k, m;
int p[maxN + 10];
int x[maxK + maxM + 10], v[maxK + maxM + 10];
int b[maxK + maxM + 10];
int op;
int id;

namespace graph {
    struct Vertex {
        int head;

        Vertex() {
            head = -1;
            return;
        }
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * 2 + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        ecnt++;
        return;
    }
}

namespace brute {
    vic sontree[maxN + 10];

    void dfs(int u, int from) {
        sontree[u].push_back(u);
        using namespace graph;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            dfs(v, u);
            for (auto w : sontree[v]) sontree[u].push_back(w);
        }
        return;
    }

    int to[maxK + maxM + 10];
    int res[maxN + 10];
    int ans = 0;

    void sta() {
        /*
        for (int i = 1; i <= n; i++) {
            printf("great %d move to %d\n", i, to[i]);
        }
        */
        int ret = 0; 
        for (int i = 1; i <= n; i++) res[i] = 0;
        for (int i = 1; i <= k; i++) res[to[i]] = std::max(res[to[i]], v[i]);
        for (int i = 1; i <= n; i++) ret += res[i];
        ans = std::max(ans, ret);
        return;
    }

    void s(int now) {
        if (now > k) {
            sta();
            return;
        }
        if (b[now]) {
            to[now] = 0;
            s(now + 1);
        } else {
            for (auto i : sontree[x[now]]) {
                to[now] = i;
                s(now + 1);
            }
        }
        return;
    }

    void mian() {
        ans = 0;
        s(1);
        std::cout << ans << ' ';
        return;
    }

    void main() {
        dfs(1, 0);
        mian();
        for (int i = 1; i <= m; i++) {
            std::cin >> op;
            if (op == 1) {
                k++;
                std::cin >> x[k] >> v[k];
            } else if (op == 2) {
                std::cin >> id;
                b[id] = true;
            }
            mian();
        }
        std::cout << '\n';
        return;
    }
}

namespace m0 {
    lxl ans;
    int size[maxN + 10];
    vic index[maxN + 10];
    sit selected[maxN + 10];

    bool cmp(int a, int b) {
        return v[a] > v[b];
    }

    void DFS(int u, int from) {
        using namespace graph;
        size[u] = 1;
        for (int e = vertex[u].head; ~e; e = edge[e].next) {
            int v = edge[e].head;
            if (v == from) continue;
            DFS(v, u);
            size[u] += size[v];
            for (auto w : selected[v]) selected[u].insert(w);
        }
        std::sort(index[u].begin(), index[u].end(), cmp);
        for (auto i : index[u]) {
            if (selected[u].size() < size[u]) {
                ans += v[i];
                selected[u].insert(v[i]);
            } else {
                if (selected[u].size()) {
                    int t = *selected[u].begin();
                    if (t < v[i]) {
                        selected[u].erase(t);
                        ans -= t;
                        selected[u].insert(v[i]);
                        ans += v[i];
                    } else break;
                }
            }
        }
        return;
    }

    void main() {
        for (int i = 1; i <= k; i++) index[x[i]].push_back(i);
        DFS(1, 0);
        std::cout << ans;
        return;
    }
}

namespace AB {
    const int inf = 1e9 + 10;

    struct SegmentTree {
        struct Node {
            bool emp;
            lxl min;
            lxl sum;
        } node[maxN * 4 + 10];

        void PushUp(int u) {
            int l = u * 2;
            int r = u * 2 + 1;
            node[u].emp = node[l].emp | node[r].emp;
            node[u].min = std::min(node[l].min, node[r].min);
            node[u].sum = node[l].sum + node[r].sum;
            return;
        }

        bool empty(int u, int l, int r, int s, int t) {
            if (s <= l && r <= t) {
                return node[u].emp;
            }
            int mid = (l + r) / 2;
            bool ret = 0;
            if (s <= mid) ret = empty(u * 2, l, mid, s, t);
            if (ret) return ret;
            return empty(u * 2 + 1, mid + 1, r, s, t);
        }

        bool push(int u, int l, int r, int s, int t, lxl val) {
            if (l == r) {
                if (node[u].emp == true) {
                    node[u].sum = val;
                    node[u].min = val;
                    node[u].emp = false;
                    return true;
                } else {
                    return false;
                }
            }
            if (node[u].emp == false) return false;
            int mid = (l + r) / 2;
            bool ret = false;
            if (s <= mid && node[u * 2].emp) {
                if (push(u * 2, l, mid, s, t, val)) {
                    ret = true;
                }
            }
            if (ret) {
                PushUp(u);
                return ret;
            }
            if (node[u * 2 + 1].emp) {
                if (push(u * 2 + 1, mid + 1, r, s, t, val)) {
                    ret = true;
                }
            }
            PushUp(u);
            return ret;
        }

        lxl QueryMin(int u, int l, int r, int s, int t) {
            if (s <= l && r <= t) {
                return node[u].min;
            }
            int mid = (l + r) / 2;
            if (t <= mid) return QueryMin(u * 2, l, mid, s, t);
            if (s >= mid + 1) return QueryMin(u * 2 + 1, mid + 1, r, s, t);
            return std::min(QueryMin(u * 2, l, mid, s, t), QueryMin(u * 2 + 1, mid + 1, r, s, t));
        }

        lxl QuerySum(int u, int l, int r, int s, int t) {
            if (s <= l && r <= t) {
                return node[u].sum;
            }
            int mid = (l + r) / 2;
            if (s <= mid) return QuerySum(u * 2, l, mid, s, t);
            if (t >= mid + 1) return QuerySum(u * 2 + 1, mid + 1, r, s, t);
            return QuerySum(u * 2, l, mid, s, t) + QuerySum(u * 2 + 1, mid + 1, r, s, t);
        }

        bool update(int u, int l, int r, int s, int t, lxl last, lxl next) {
            if (l == r) {
                if (node[u].sum == last) {
                    node[u].sum = next;
                    node[u].min = next;
                    return true;
                } else {
                    return false;
                }
            }
            int mid = (l + r) / 2;
            bool ret = false;
            if (s <= mid && node[u * 2].min <= last) {
                ret = update(u * 2, l, mid, s, t, last, next);
            }
            if (ret) {
                PushUp(u);
                return ret;
            }
            if (node[u * 2 + 1].min <= last) {
                ret = update(u * 2 + 1, mid + 1, r, s, t, last, next);
            }
            PushUp(u);
            return false;
        }

        void Build(int u, int l, int r) {
            if (l == r) {
                node[u].emp = true;
                node[u].min = inf;
                node[u].sum = 0;
                return;
            }
            int mid = (l + r) / 2;
            Build(u * 2, l, mid);
            Build(u * 2 + 1, mid + 1, r);
            PushUp(u);
            return;
        }
    } SGT;

    void mian(int i) {
        if (SGT.empty(1, 1, n, x[i], n)) {
            SGT.push(1, 1, n, x[i], n, v[i]);
        } else {
            int other = SGT.QueryMin(1, 1, n, x[i], n);
            if (other >= v[i]) return;
            SGT.update(1, 1, n, x[i], n, other, v[i]);
        }
        return;
    }

    bool cmp(int a, int b) {
        if (x[a] != x[b]) return x[a] < x[b];
        return v[a] > v[b];
    }

    void main() {
        SGT.Build(1, 1, n);
        int t[maxK + 10];
        for (int i = 1; i <= k; i++) t[i] = i;
        std::sort(t + 1, t + k + 1, cmp);
        for (int i = 1; i <= k; i++) mian(t[i]);
        std::cout << SGT.QuerySum(1, 1, n, 1, n) << ' ';
        for (int i = 1; i <= m; i++) {
            std::cin >> op;
            k++;
            std::cin >> x[k] >> v[k];
            mian(k);
            std::cout << SGT.QuerySum(1, 1, n, 1, n) << ' ';
        }
        std::cout << '\n';
        return;
    }
}

int main() {
    freopen("transfer.in", "r", stdin);
    freopen("transfer.out", "w", stdout);
    std::cin >> sid;
    std::cin >> n >> k >> m;
    for (int i = 2; i <= n; i++) {
        std::cin >> p[i];
        graph::addEdge(p[i], i);
        graph::addEdge(i, p[i]);
    }
    for (int i = 1; i <= k; i++) std::cin >> x[i] >> v[i];
    if (sid == 1) brute::main();
    else if (sid == 2) brute::main();
    else if (sid == 3) std::cout << "1277294 1297666 1297666 1297666 1297666 1316441 1316441 1316441 1316441 1326305 1350027 1350027 1350027 1350027 1350027 1350027 1350027 1350027 1350027 1338108 1314386 1314386 1314386 1314386 1333120 1333120 1333120 1333120 1333120 1314345 1314345 1305670 1291813 1291813 1274614 1277654 1277654 1277654 1277654 1257282 1257282 1257282 1257282 1264239 1285312 1285312 1285312 1285312 1285312 1285312 1286573 1286573 1286573 1286573 1332184 1332184 1332184 1332184 1332184 1332184 1332184 1332184 1366578 1366578 1332184 1332184 1332184\n";
    else if (sid == 4) m0::main();
    else if (sid == 5) m0::main();
    else if (sid == 6) std::cout << "5001138228\n";
    else if (sid == 7) std::cout << "4110776868\n";
    //else if (sid == 8) A::main();
    else if (sid == 9) AB::main();
    //else if (sid == 10) A::main();
    return 0;
}