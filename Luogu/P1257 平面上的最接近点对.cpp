#include <cstdio>
#include <cmath>
#include <algorithm>

const int inf = 1e9 + 10;
const int maxN = 1e4 + 10;

int n;
struct Node {
	double x, y;
	bool operator<(Node other) const {
		return x < other.x;
	}
} point[maxN];

double calc(Node x, Node y) {
	double deltaX = x.x - y.x;
	double deltaY = x.y - y.y;
	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &point[i].x, &point[i].y); 
	std::sort(point + 1, point + n + 1);
	double ans = inf;
	for (int i = 1; i <= n; i++) for(int j = 1; j <= 5 && i + j <= n; j++) ans = std::min(ans, calc(point[i], point[i + j]));
	printf("%.4lf", ans);
	return 0;
} 