#include <cstdio>

const int maxn = 1e5+ 10;
const int mod = 99991;

int n;
int a[10];

struct Hash {
    struct Node {
        int next;
        int a[10];
    };

    int cnt;
    int head[maxn];
    Node node[maxn];

    int H(int *a) {
        long long ans = 1;
        for (int i = 0; i < 6; i++) ans = (ans * a[i]) % mod;
        for (int i = 0; i < 6; i++) ans = (ans + a[i]) % mod;
        return ans;
    }

    void Add(int *a) {
        int hashA = H(a);
        cnt++;
        node[cnt].next = head[hashA];
        head[hashA] = cnt;
        for (int i = 0; i < 6; i++) node[cnt].a[i] = a[i];
        return;
    }

    bool Check(int *a) {
        int hashA = H(a);
        for (int i = head[hashA]; i; i = node[i].next) {
            for (int j = 0; j < 6; j++) {
                bool equal = true;
                for (int k = 0; k < 6; k++) {
                    if (node[i].a[(j + k) % 6] != a[k]) equal = false;
                }
                if (equal) return true;
                equal = true;
                for (int k = 0; k < 6; k++) {
                    if (node[i].a[(j - k + 6) % 6] != a[k]) equal = false;
                }
                if (equal) return true;
            }
        }
        return false;
    }
};

Hash snowFlake;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < 6; j++) scanf("%d", &a[j]);
        if (snowFlake.Check(&a[0])) {
            printf("Twin snowflakes found.\n");
            return 0;
        }
        snowFlake.Add(a);
    }
    printf("No two snowflakes are alike.\n");
    return 0;
}