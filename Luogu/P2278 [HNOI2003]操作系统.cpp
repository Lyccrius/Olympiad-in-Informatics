#include <cstdio>
#include <queue>

const int maxN = 1.5e4 + 10;

struct Process {
	int id;
	int get;
	int time;
	int level;
	
	bool operator<(Process other) const {
		if (level != other.level) return level < other.level;
		return get > other.get;
	}
};

std::priority_queue<Process> waiting;

int main() {
	int id, get, time, level;
	int now = -1;
	while (scanf("%d%d%d%d", &id, &get, &time, &level) != EOF) {
		while (!waiting.empty() && now + waiting.top().time <= get) {
			now += waiting.top().time;
			printf("%d %d\n", waiting.top().id, now);
			waiting.pop();
		}
		if (!waiting.empty()) {
			Process cache = waiting.top();
			waiting.pop();
			cache.time -= get - now;
			waiting.push(cache);
		}
		waiting.push((Process){id, get, time, level});
		now = get;
	}
	while (!waiting.empty()) {
		now += waiting.top().time;
		printf("%d %d\n", waiting.top().id, now);
		waiting.pop();
	}
	return 0;
}