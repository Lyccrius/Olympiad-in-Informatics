#include <cstdio>
#include <algorithm>
#include <vector>

const int maxN = 1e7;
const int maxM = 1e4;

int N, M;
int A[maxM + 10], B[maxM + 10];

std::vector<int> range;
bool appeared;
int ans;

struct SegmentTree {
    struct Node {
        int l, r;
        int lNode;
        int rNode;
        bool vis;
    } node[maxM << 5];

    int cnt;
    int root;

    void Clone(int &xNode) {
        cnt++;
        node[cnt] = node[xNode];
        xNode = cnt;
        return;
    }

    void Build(int &xNode, int l, int r) {
        Clone(xNode);
        node[xNode].l = l;
        node[xNode].r = r;
        if (l == r) return;
        int mid = (node[xNode].l + node[xNode].r) >> 1;
        Build(node[xNode].lNode, l, mid);
        Build(node[xNode].rNode, mid + 1, r);
        return;
    }

    void PushUp(int xNode) {
        node[xNode].vis = node[node[xNode].lNode].vis && node[node[xNode].rNode].vis;
        return;
    }

    void Modify(int xNode, int l, int r) {
        if (node[xNode].vis) return;
        if (l <= node[xNode].l && node[xNode].r <= r) {
            node[xNode].vis = true;
            appeared = true;
            return;
        }
        if (node[xNode].l == node[xNode].r) return;
        int mid = (node[xNode].l + node[xNode].r) >> 1;
        if (l <= mid) Modify(node[xNode].lNode, l, r);
        if (r >= mid + 1) Modify(node[xNode].rNode, l, r);
        PushUp(xNode);
        return;
    }
} SGT;

void Discrete() {
    for (int i = 1; i <= M; i++) {
        range.push_back(A[i] - 1);
        range.push_back(A[i]);
        range.push_back(A[i] + 1);
        range.push_back(B[i] - 1);
        range.push_back(B[i]);
        range.push_back(B[i] + 1);
    }
    std::sort(range.begin(), range.end());
    range.erase(std::unique(range.begin(), range.end()), range.end());
    for (int i = 1; i <= M; i++) {
        A[i] = std::lower_bound(range.begin(), range.end(), A[i]) - range.begin();
        B[i] = std::lower_bound(range.begin(), range.end(), B[i]) - range.begin();
    }
    return;
}

int main() {
    scanf("%d%d", &N, &M);
    SGT.Build(SGT.root, 1, M * 5);
    for (int i = 1; i <= M; i++) scanf("%d%d", &A[i], &B[i]);
    Discrete();
    for (int i = M; i >= 1; i--) {
        appeared = false;
        SGT.Modify(SGT.root, A[i], B[i]);
        if (appeared) ans++;
    }
    printf("%d\n", ans);
    return 0;
}