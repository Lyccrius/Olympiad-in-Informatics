#include <cstdio>
#include <algorithm>

const int maxN = 1e5 + 10;
const int maxT = 1e9;

int T;
int w, h;
int n;
struct Event {
	double time;
	int type;

	bool operator<(Event other) const {
		if (time != other.time) return time < other.time;
		return type > other.type;
	}
};
Event events[maxN * 2];
int ecnt;

void addEvent(double time, int type) {
	ecnt++;
	events[ecnt].time = time;
	events[ecnt].type = type;
	return;
}

void update(int pos, int delta, int limit, double& begin, double& end) {
	if (delta == 0) {
		if (pos <= 0 || pos >= limit) end = begin;
	} else if (delta > 0) {
		begin = std::max(begin, -(double)pos / delta);
		end = std::min(end, (double)(limit - pos) / delta);
	} else {
		begin = std::max(begin, (double)(limit - pos) / delta);
		end = std::min(end, -(double)pos / delta);
	}
	return;
}

int main() {
	scanf("%d", &T);
	for (int kase = 1; kase <= T; kase++) {
		scanf("%d%d", &w, &h);
		scanf("%d", &n);
		ecnt = 0;
		for (int i = 1; i <= n; i++) {
			int x, y;
			int a, b;
			scanf("%d%d%d%d", &x, &y, &a, &b);
			double begin = 0;
			double end = maxT;
			update(x, a, w, begin, end);
			update(y, b, h, begin, end);
			if (begin < end) {
				addEvent(begin, 0);
				addEvent(end, 1);
			}
		}
		std::sort(events + 1, events + ecnt + 1);
		int ans = 0;
		int cnt = 0;
		for (int i = 1; i <= ecnt; i++) {
			if (events[i].type) --cnt;
			else ans = std::max(++cnt, ans);
		}
		printf("%d\n", ans);
	}
	return 0;
}