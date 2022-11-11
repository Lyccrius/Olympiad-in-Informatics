#include <cstdio>
#include <algorithm>
#include <iostream>

const int maxn = 1e4 + 10;
const int root = 1;

int n;

long long ans;

struct Commodity {
    int p;
    int d;

    bool operator<(Commodity other) const {
        if (d != other.d) return d < other.d;
        return p > other.p;
    }
};

Commodity supermarket[maxn];

struct Heap {
    int heap[maxn];
    int cnt;

    void PushUp(int xNode) {
        while (xNode != root) {
            if (heap[xNode] < heap[xNode / 2]) {
                std::swap(heap[xNode], heap[xNode / 2]);
                xNode /= 2;
            } else break;
        }
        return;
    }

    void PushDown(int xNode) {
        int sNode = xNode * 2;
        while (sNode <= cnt) {
            if (sNode < cnt && heap[sNode] > heap[sNode + 1]) sNode++;
            if (heap[sNode] < heap[xNode]) {
                std::swap(heap[sNode], heap[xNode]);
                xNode = sNode;
                sNode = xNode * 2;
            } else break;
        }
        return;
    }

    void Push(int val) {
        cnt++;
        heap[cnt] = val;
        PushUp(cnt);
        return;
    }

    void Pop() {
        if (!cnt) return;
        heap[root] = heap[cnt];
        cnt--;
        PushDown(root);
        return;
    }

    void Remove(int xNode) {
        heap[xNode] = heap[cnt];
        cnt--;
        PushUp(xNode);
        PushDown(xNode);
        return;
    }

    int Top() {
        return heap[root];
    }

    void Clear() {
        cnt = 0;
        return;
    }

    bool Empty() {
        return !cnt;
    }
};

Heap sell;

int main() {
    while (std::cin >> n) {
        ans = 0;
        sell.Clear();
        for (int i = 1; i <= n; i++) scanf("%d%d", &supermarket[i].p, &supermarket[i].d);
        std::sort(supermarket + 1, supermarket + n + 1);
        for (int i = 1; i <= n; i++) {
            if (supermarket[i].d > sell.cnt) sell.Push(supermarket[i].p);
            else if (supermarket[i].d == sell.cnt && supermarket[i].p > sell.Top()) {
                sell.Pop();
                sell.Push(supermarket[i].p);
            }
        }
        while (!sell.Empty()) {
            ans += sell.Top();
            sell.Pop();
        }
        printf("%lld\n", ans);
    }
    return 0;
}