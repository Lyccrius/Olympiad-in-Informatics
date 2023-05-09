#include <iostream>
#include <map>

typedef long long lxl;
typedef std::map<lxl, lxl> mll;

lxl x, y;
mll f;

lxl DFS(lxl now) {
    if (now == x) return 0;
    if (now < x) return x - now;
    if (f[now]) return f[now];
    f[now] = now - x;
    if (now & 1) f[now] = std::min(f[now], std::min(DFS(now - 1), DFS(now + 1)) + 1);
    else f[now] = std::min(f[now], DFS(now / 2) + 1);
    return f[now];
}

int main() {
    std::cin >> x >> y;
    std::cout << DFS(y) << '\n';
    return 0;
}