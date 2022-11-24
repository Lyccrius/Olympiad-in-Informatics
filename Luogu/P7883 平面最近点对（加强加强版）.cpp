#include <cstdio>
#include <cmath>
#include <algorithm>

const long long inf = 1e18 + 10;
const int maxN = 4e5 + 10;

int n;
struct Node {
	double x, y;
	double xx, yy;
	bool operator<(Node other) const {
		return xx * yy < other.xx * other.yy;
	}
} point[maxN];

double calc(Node x, Node y) {
	double deltaX = x.x - y.x;
	double deltaY = x.y - y.y;
	return deltaX * deltaX + deltaY * deltaY;
}

int main() {
	double s = std::sin(1);
	double c = std::cos(1);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &point[i].x, &point[i].y); 
		point[i].xx = point[i].x * c - point[i].y * s;
		point[i].yy = point[i].x * s + point[i].y * c;
	}
	std::sort(point + 1, point + n + 1);
	double ans = inf;
	int k = std::min(100, n);
	for (int i = 1; i <= n; i++) for(int j = 1; j <= k && i + j <= n; j++) ans = std::min(ans, calc(point[i], point[i + j]));
	printf("%.0lf", ans);
	return 0;
} 