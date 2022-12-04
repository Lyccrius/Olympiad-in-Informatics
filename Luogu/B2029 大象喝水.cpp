#include <cstdio>
#include <cmath>

const int inf = 1e9 + 10;;
const double pi = std::acos(-1);

int h, r;

int main() {
    scanf("%d%d", &h, &r);
    double v = pi * r * r * h;
    int tot = 20 * 1000;
    int cnt = 0;
    for (int i = 20; i >= 0; i--) if (tot > v * (1 << i)) tot -= v * (1 << i), cnt += (1 << i);
    cnt++;
    printf("%d\n", cnt);
    return 0;
}