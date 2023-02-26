#include <iostream>
#include <queue>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

typedef long long lxl;

lxl read(){
    lxl ret = 0;
	bool f = 0;
	char c = getchar();
	while (!isdigit(c)) f |= (c == '-'), c = getchar();
	while (isdigit(c)) ret = ret * 10 + (c & 15), c = getchar();
	return f ? - ret : ret;
} 

const lxl maxN = 1e7;
const lxl maxA = 1e5;

int n;
int a;
int c[maxA + 10];
std::queue<lxl> q1;
std::queue<lxl> q2;
lxl ans;

lxl get() {
    lxl f1 = maxN * maxA + 10;
    lxl f2 = maxN * maxA + 10;
    if (!q1.empty()) f1 = q1.front();
    if (!q2.empty()) f2 = q2.front();
    if (f1 <= f2) {
        q1.pop();
        return f1;
    } else {
        q2.pop();
        return f2;
    }
}

int main() {
    //promote();
    //std::cin >> n;
    //for (int i = 1; i <= n; i++) std::cin >> a, c[a]++;
    n = read();
    for (int i = 1; i <= n; i++) c[read()]++;
    for (int i = 1; i <= maxA; i++) for (int j = 1; j <= c[i]; j++) q1.push(i);
    for (int i = 1; i < n; i++) {
        lxl x = get();
        lxl y = get();
        ans += x + y;
        q2.push(x + y);
    }
    std::cout << ans << '\n';
    return 0;
}