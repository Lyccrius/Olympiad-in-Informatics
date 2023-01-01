#include <cstdio>
#include <algorithm>
#include <vector>

const long long maxN = 2e5;

long long T;

long long n;
long long a[maxN + 10];

std::vector<long long> appear[maxN + 10];
long long last[maxN + 10];
long long next[maxN + 10];

void Discrete() {
    std::vector<long long> range;
    for (long long i = 1; i <= n; i++) range.push_back(a[i]);
    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());
    for (long long i = 1; i <= n; i++) a[i] = std::lower_bound(range.begin(), range.end(), a[i]) - range.begin() + 1;
    return;
}

struct SegmentTree {
    struct Node {
        long long l, r;
        long long lNode;
        long long rNode;
        long long sum;
        long long tag;

        Node() {
            l = 0;
            r = 0;
            lNode = 0;
            rNode = 0;
            sum = 0;
            tag = 0;
            return;
        }
    } node[(maxN << 2) + 10];

    long long root;
    long long cnt;

    SegmentTree() {
        root = 0;
        cnt = 0;
        return;
    }

    void Clone(long long &xNode) {
        cnt++;
        node[cnt] = node[xNode];
        xNode = cnt;
        return;
    }

    void Build(long long &xNode, long long l, long long r) {
        if (xNode == 0) Clone(xNode);
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) return;
        //printf("Building [%lld, %lld]\n", l, r);
        long long mid = (l + r) >> 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        return;
    }

    void PushUp(long long xNode) {
        if (node[xNode].tag) node[xNode].sum = node[xNode].r - node[xNode].l + 1;
        else node[xNode].sum = node[node[xNode].lNode].sum + node[node[xNode].rNode].sum;
        //printf("[%lld, %lld]: %lld\n", node[xNode].l, node[xNode].r, node[xNode].sum);
        return;
    }

    void Modify(long long xNode, long long l, long long r,long long val) {
        //printf("Modifying [%lld, %lld]: %lld\n", l, r, val);
        if (l <= node[xNode].l && node[xNode].r <= r) {
            node[xNode].tag += val;
            PushUp(xNode);
            return;
        }
        long long mid = (node[xNode].l + node[xNode].r) >> 1;
        if (l <= mid) Modify(node[xNode].lNode, l, r, val);
        if (r >= mid + 1) Modify(node[xNode].rNode, l, r, val);
        PushUp(xNode);
        return;
    }

    void Clear() {
        cnt = 0;
        root = 0;
        for (long long i = 0; i <= (n * 4); i++) {
            node[i].l = 0;
            node[i].r = 0;
            node[i].lNode = 0;
            node[i].rNode = 0;
            node[i].tag = 0;
            node[i].sum = 0;
        }
        return;
    }
} SGT;

struct Event {
    long long x;
    long long y1, y2;
    long long delta;

    bool operator<(const Event& other) const {
        if (x != other.x) return x < other.x;
        return delta < other.delta;
    }
};

std::vector<Event> event;

void mian() {
    scanf("%lld", &n);
    for (long long i = 1; i <= n; i++) scanf("%lld", &a[i]);
    Discrete();
    for (long long i = 1; i <= n; i++) appear[i].clear();
    for (long long i = 1; i <= n; i++) appear[a[i]].push_back(i);
    for (long long i = 1; i <= n; i++) {
        for (long long j = 0; j < appear[i].size(); j++) {
            if (appear[i].size() == 1) {
                last[appear[i][j]] = 0;
                next[appear[i][j]] = n + 1;
                continue;
            }
            if (j == 0) {
                last[appear[i][j]] = 0;
                next[appear[i][j]] = appear[i][j + 1];
                continue;
            }
            if (j == appear[i].size() - 1) {
                last[appear[i][j]] = appear[i][j - 1];
                next[appear[i][j]] = n + 1;
                continue;
            }
            last[appear[i][j]] = appear[i][j - 1];
            next[appear[i][j]] = appear[i][j + 1];
        }
    }
    event.clear();
    for (long long i = 1; i <= n; i++) {
        long long x1 = last[i] + 1;
        long long x2 = i;
        long long y1 = i;
        long long y2 = next[i] - 1;
        event.push_back((Event){x1, y1, y2, 1});
        event.push_back((Event){x2 + 1, y1, y2, -1});
    }
    std::sort(event.begin(), event.end());
    long long head = 0;
    long long tot = 0;
    SGT.Clear();
    SGT.Build(SGT.root, 1, n);
    for (long long i = 1; i <= n; i++) {
        while (head < event.size() && event[head].x <= i) {
            SGT.Modify(SGT.root, event[head].y1, event[head].y2, event[head].delta);
            head++;
        }
        tot += SGT.node[SGT.root].sum;
    }
    if (tot == n * (n + 1) / 2) printf("non-boring\n");
    else printf("boring\n");
    return;
}

int main() {
    scanf("%lld", &T);
    while (T--) mian();
    return 0;
}

/*
[1, 5], 1
[2, 5], 1
[3, 5], 1
[4, 5], 1
[5, 5], 1
5
[1, 5], -1
4
[2, 5], -1
3
[3, 5], -1
2
[4, 5], -1
1
non-boring
[2, 5], 1
[1, 1], 1
[5, 5], 1
[3, 5], 1
[4, 5], 1
[1, 5], 1
5
[1, 1], -1
[2, 2], 1
[1, 5], -1
4
[2, 5], -1
[2, 2], -1
[3, 3], 1
3
[3, 5], -1
[3, 3], -1
[4, 4], 1
2
[4, 5], -1
[4, 4], -1
[5, 5], 1
1
non-boring
[1, 1], 1
[3, 5], 1
[2, 3], 1
[1, 4], 1
[2, 5], 1
[1, 5], 1
[5, 5], 1
[3, 5], 1
[4, 5], 1
5
[1, 1], -1
[1, 4], -1
[5, 5], 1
[1, 5], -1
[2, 2], 1
4
[3, 3], 1
[2, 2], -1
[4, 5], 1
[2, 5], -1
[2, 3], -1
3
[3, 5], -1
[3, 3], -1
[4, 4], 1
[3, 5], -1
2
[4, 5], -1
[4, 5], -1
[5, 5], 1
[4, 4], -1
1
non-boring
[3, 5], 1
[1, 1], 1
[3, 5], 1
[1, 1], 1
[4, 5], 1
[3, 5], 1
[1, 5], 1
[2, 5], 1
[5, 5], 1
[2, 3], 1
[1, 4], 1
5
[1, 1], -1
[1, 4], -1
[5, 5], 1
[1, 5], -1
[2, 2], 1
[1, 1], -1
[2, 3], 1
4
[4, 5], 1
[2, 3], -1
[4, 4], 1
[2, 3], -1
[2, 5], -1
[2, 2], -1
[3, 3], 1
3
[3, 5], -1
[3, 3], -1
[3, 5], -1
[4, 4], 1
[3, 5], -1
2
[4, 4], -1
[5, 5], 1
[4, 5], -1
[4, 5], -1
[4, 4], -1
[5, 5], 1
1
non-boring
*/