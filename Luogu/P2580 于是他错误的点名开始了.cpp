#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>

int n, m;
std::string name;
std::map<std::string, int> list;

int main() {
    scanf("%d", &n);
    while (n--) {
    	std::cin >> name;
    	list[name] = 1;
    }
    scanf("%d", &m);
    while (m--) {
    	std::cin >> name;
    	if (list[name] == 1) {
			list[name]++;
			printf("OK\n");
			continue;
		}
    	if (list[name] == 2) {
			printf("REPEAT\n");
			continue;
		}
    	printf("WRONG\n");
    }
	return 0;
}