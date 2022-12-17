#include <iostream>
#include <string>
#include <map>

const int maxN = 1e5 + 10;

int n;
int opt;
std::string name;
int score;

std::map<std::string, bool> vis;
std::map<std::string, long long> sco;
int cnt;

void modify() {
	std::cin >> name;
	std::cin >> score;
	if (vis[name] == false) cnt++;
	vis[name] = true;
	sco[name] = score;
	std::cout << "OK" << std::endl;
	return;
}

void query() {
	std::cin >> name;
	if (vis[name] == false) std::cout << "Not found" << std::endl;
	else std::cout << sco[name] << std::endl;
	return;
}

void delet() {
	std::cin >> name;
	if (vis[name] == false) std::cout << "Not found" << std::endl;
	else {
		vis[name] = false;
		cnt--;
		std::cout << "Deleted successfully" << std::endl;
	}
	return;
}

void count() {
	std::cout << cnt << std::endl;
	return;
}

int main() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> opt;
		if (opt == 1) modify();
		if (opt == 2) query();
		if (opt == 3) delet();
		if (opt == 4) count();
	}
	return 0;
}