#include <cstdio>
#include <cmath>

const int maxN = 60;

int n;
struct Circle {
    int x, y;
    int r;
} circles[maxN];

double dist(int x1,int y1,int x2,int y2) {
    int deltaX = x1 - x2;
    int deltaY = y1 - y2;
    double dis = std::sqrt(deltaX * deltaX + deltaY * deltaY);
	return dis;
}

int main(){
	int x1, y1;
    int x2, y2;
    int ans = 0;
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%d",&circles[i].x);
	for (int i=1;i<=n;i++) scanf("%d",&circles[i].y);
	for (int i=1;i<=n;i++) scanf("%d",&circles[i].r);
	scanf("%d%d", &x1, &y1);
	scanf("%d%d", &x2, &y2);
	for (int i = 1; i <= n; i++) if((dist(x1, y1, circles[i].x, circles[i].y) < circles[i].r) ^
                                    (dist(x2, y2, circles[i].x, circles[i].y) < circles[i].r)) ans++;
	printf("%d\n",ans);
	return 0;
}