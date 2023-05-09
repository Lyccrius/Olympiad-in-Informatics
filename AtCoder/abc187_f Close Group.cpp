#include <iostream>
#include <vector>
#include <cstring>

typedef std::vector<int> vic;

const int maxN = 18;
const int maxM = 153;

int n, m;
int u, v;
int a[maxN + 10][maxN + 10];
int f[(1 << (maxN + 1))];

bool check(int s) {
    //printf("checking %d\n", s);
    vic q;
    for (int i = 1; i <= n; i++) {
        if (s & (1 << i)) {
            q.push_back(i);
        }
    }
    for (int i = 0; i < q.size(); i++) {
        for (int j = i + 1; j < q.size(); j++) {
            if (a[q[i]][q[j]] == 0) {
                //printf("failed at %d, %d\n", q[i], q[j]);
                return false;
            }
        }
    }
    return true;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> u >> v;
        a[u][v] = true;
        a[v][u] = true;
    }
    std::memset(f, 0x3f, sizeof(f));
    for (int i = 2; i < (1 << (n + 1)); i++) {
        //printf("i = %d\n", i);
        if (check(i)) {
            //printf("%d complete\n", i);
            f[i] = 1;
        } else {
            for (int j = i; j; j = (j - 1) & i) {
                if (j == i) continue;
                int k = i ^ j;
                f[i] = std::min(f[i], f[j] + f[k]);
            }
        }
    }
    std::cout << f[(1 << (n + 1)) - 1] << '\n';
    return 0;
}