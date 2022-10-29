#include <cstdio>
#include <cmath>
#include <algorithm>

const int maxn = 1e6 + 10;
const int maxs = 1e3 + 10;

struct BlockArray {
    int n;
    int s;

    struct Node {
        int val;
        int belong;

        Node() {
            val = 0;
        }
    };

    struct Block {
        int sum;
        int tag;

        int start;
        int end;

        Block() {
            sum = 0;
            tag = 0;
            start = -1;
            end = -1;
        }
    };

    struct Node array[maxn];
    struct Block block[maxs];

    int sortedArray[maxn];
    bool sorted[maxs];

    void Init() {
        for (int i = 1; i <= n; i++) {
            array[i].belong = (i - 1) / s + 1;
            if (block[array[i].belong].start == -1) {
                block[array[i].belong].start = i;
            }
            block[array[i].belong].end = i;
            block[array[i].belong].sum += array[i].val;
        }
    }

    void Sort(int x) {
        int start = block[x].start;
        int end = block[x].end;
        for (int i = start; i <= end; i++) {
            sortedArray[i] = array[i].val;
        }
        std::sort(sortedArray + start, sortedArray + end + 1);
        sorted[x] = true;

        return;
    }

    void Add(int l, int r, int x) {
        int startBelong = array[l].belong;  
        int endBelong = array[r].belong;

        if (startBelong == endBelong) {
            for (int i = l; i <= r; i++) {
                array[i].val += x;
                block[startBelong].sum += x;
            }

            Sort(startBelong);

            return;
        }

        for (int i = l; array[i].belong == startBelong; i++) {
            array[i].val += x;
            block[startBelong].sum += x;
        }
        
        for (int i = startBelong + 1; i < endBelong; i++) {
            block[i].tag += x;
            block[i].sum += x * s;
        }

        for (int i = r; array[i].belong == endBelong; i--) {
            array[i].val += x;
            block[endBelong].sum += x;
        }

        Sort(startBelong);
        Sort(endBelong);

        return;
    }

    int Greater(int l, int r, int x) {
        int ans = 0;
        int startBelong = array[l].belong;
        int endBelong = array[r].belong;

        if (startBelong == endBelong) {
            for (int i = l; i <= r; i++) {
                if (array[i].val + block[startBelong].tag >= x) {
                    ans ++;
                }
            }

            return ans;
        }

        for (int i = l; i <= block[startBelong].end; i++) {
            int tag = block[startBelong].tag;
            if (array[i].val + tag >= x) {
                ans++;
            }
        }

        for (int i = startBelong + 1; i < endBelong; i++) {
            if (!sorted[i]) {
                Sort(i);
            }
            ans += block[i].end - (std::lower_bound(sortedArray + block[i].start, 
                                                    sortedArray + block[i].end + 1, 
                                                    x - block[i].tag) - sortedArray) + 1;
        }

        for (int i = block[endBelong].start; i <= r; i++) {
            int tag = block[endBelong].tag;
            if (array[i].val + tag >= x) {
                ans++;
            }
        }

        return ans;
    }
};

struct BlockArray blockArray;

int main() {
    int N, Q;
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &blockArray.array[i].val);
    }

    blockArray.n = N;
    blockArray.s = sqrt(N);
    blockArray.Init();

    char opt;
    int L, R, W, C;

    for (int i = 1; i <= Q; i++) {
        scanf(" %c", &opt);
        switch(opt) {
            case 'M': {
                scanf("%d %d %d", &L, &R, &W);
                blockArray.Add(L, R, W);
                break;
            }
            case 'A': {
                scanf("%d %d %d", &L, &R, &C);
                int ans = blockArray.Greater(L, R, C);
                printf("%d\n", ans);
                break;
            }
        }
    }

    return 0;
}