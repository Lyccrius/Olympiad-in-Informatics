#include <cstdio>
#include <cmath>
#include <map>

const int maxN = 1e9;

std::map<int, int> res;

int T;
int n;
/*
void DFS(int x, int dep) {
    if (dep > 15) return;
    //if (x < 0) return;
    if (res[x]) return;
    res[x] = dep;
    DFS(x + (1 << (dep - 1)), dep + 1);
    DFS(x - (1 << (dep - 1)), dep + 1);
    return;
}
*/

int lowbit(int x) {
    return x & -x;
}

void mian() {
    scanf("%d", &n);
    int res;
    if ((n & 1) == 0) res = -2;
    else res = std::log2(n);
    printf("%d\n", res + 1);
    return;
}

int main() {
    //DFS(0, 1);
    scanf("%d", &T);
    while (T--) mian();
    /*
    for (int i = 1; i <= 1024; i++) {
        printf("%d ", i);
        for (int p = 10; p >= 0; p--) {
            if ((i >> p) & 1) printf("1");
            else printf(" ");
        }
        printf(" %d\n", res[i] - 1);
    }
    */
    return 0;
}