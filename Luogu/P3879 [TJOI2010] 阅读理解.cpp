#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <map>

const int maxN = 1e5 + 10;

int N;
int L;
std::string s;
int M;
std::map<std::string, std::vector<int> > a;
int cnt[maxN];

int main() {
	std::cin >> N;
	for (int i = 1; i <= N; i++){
		std::cin >> L;
		for (int j = 1; j <= L; j++) std::cin >> s, a[s].push_back(i);
	}
	std::cin >> M;
	for (int i = 1; i <= M; i++) {
		std::cin >> s;
		std::memset(cnt, 0, sizeof(cnt));
		for (int j = 0; j < a[s].size(); j++) if(cnt[a[s][j]] == 0) {
			std::cout << a[s][j] << " ";
			cnt[a[s][j]]++;
		}
		std::cout << std::endl;
	}
	return 0;
}