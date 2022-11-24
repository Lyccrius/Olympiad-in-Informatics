#include <cstdio>
#include <string>
#include <algorithm>
#include <iostream>

const int maxN = 1e5 + 10;
std::string str;
std::string model[maxN], essay[maxN];
int tot;
int cnt;
int res;
int T;

int main() {
    while (std::getline(std::cin, str) && str != "EOF") {
        tot++;
		for (char ch : str) {
			if (ch == '<') {
				if (!model[tot].empty()) model[tot].pop_back();
			} else model[tot].push_back(ch);
		}
	}
	while (std::getline(std::cin, str) && str != "EOF") {
		cnt++;
		if (cnt > tot) break;
		for (char ch : str) {
			if (ch == '<') {
				if (!essay[cnt].empty()) essay[cnt].pop_back();
			} else essay[cnt].push_back(ch);
		}
		for (int i = 0; i < std::min(model[cnt].size(), essay[cnt].size()); i++) {
			res += model[cnt][i] == essay[cnt][i];
		}
	}
	scanf("%d", &T);
	printf("%d\n", (int)(res * 60.0 / T + 0.5));
	return 0;
}