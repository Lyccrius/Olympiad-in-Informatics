#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

char mirror[40] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";

char str[40];

char rev(char x) {
	if (std::isalpha(x)) return mirror[x - 'A'];
	return mirror[x - '0' + 25];
}

int main() {
	while (scanf("%s", str + 1) != EOF) {
		int len = std::strlen(str + 1);
		bool p = true;
		bool m = true;
		for (int i = 1; i <= (len + 1) / 2; i++) {
			if (str[i] != str[len - i + 1]) p = false;
			if (rev(str[i]) != str[len - i + 1]) m = false;
		}
		if (m) {
			if (p) printf("%s -- is a mirrored palindrome.\n\n", str + 1);
			else printf("%s -- is a mirrored string.\n\n", str + 1);
		} else {
			if (p) printf("%s -- is a regular palindrome.\n\n", str + 1);
			else printf("%s -- is not a palindrome.\n\n", str + 1);
		}
	}
	return 0;
}