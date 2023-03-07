#include <iostream>
#include <algorithm>

typedef long long lxl;

const int maxN = 3e5;
const int maxP = 3e5;
const int sqrN = 550;

int n;
int w[maxN + 10];
int p;
int B;
lxl ans[maxN + 10];

struct Query {
    int a;
    int b;
    int i;
    lxl s;
} q[maxP + 10];

bool cmpByB(const Query &x, const Query &y) {
    return x.b < y.b;
}

bool cmpByI(const Query &x, const Query &y) {
    return x.i < y.i;
}

void init(int b) {
    for (int i = n; i > n - b; i--) ans[i] = w[i];
    for (int i = n - b; i >= 1; i--) ans[i] = w[i] + ans[i + b];
    return;
}

lxl query(lxl a, lxl b) {
    if (b <= sqrN) {
        if (B != b) {
            B = b;
            init(b);
        }
        return ans[a];
    }
    if (b < sqrN) return ans[a];
    lxl ret = 0;
    while (a <= n) ret += w[a], a += b;
    return ret;
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> w[i];
    std::cin >> p;
    for (int i = 1; i <= p; i++) std::cin >> q[i].a >> q[i].b;
    for (int i = 1; i <= p; i++) q[i].i = i; std::sort(q + 1, q + p + 1, cmpByB);
    for (int i = 1; i <= p; i++) q[i].s = query(q[i].a, q[i].b); std::sort(q + 1, q + p + 1, cmpByI);
    for (int i = 1; i <= p; i++) std::cout << q[i].s << '\n';
    return 0;
}