#include <cstdio>
#include <cstring>
#include <stack>

const int maxN = 255 + 10;

char expression[maxN];
std::stack<char> bracket;

int main() {
	scanf("%s", &expression);
	bool overFlow = false;
	for (int i = 0; i < std::strlen(expression); i++) {
		if (expression[i] == '@') break;
		switch(expression[i]) {
			case '(': bracket.push(expression[i]); break;
			case ')': if (!bracket.empty()) bracket.pop(); else overFlow = true; break;
		}
	}
	if (!bracket.empty() || overFlow) printf("NO\n");
	else printf("YES");
	return 0;
}