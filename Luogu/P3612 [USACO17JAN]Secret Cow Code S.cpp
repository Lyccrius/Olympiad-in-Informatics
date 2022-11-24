#include <cstdio>
#include <cstring>

const long long maxN = 1e18 + 10;

long long N;
char str[30 + 10];

int main() {
    scanf("%s %lld", str + 1, &N);
	int len = std::strlen(str + 1);
    while (len < N) {
        long long i = len;
        while (N > i * 2) i *= 2;
        N -= (i + 1);
        if (N == 0) N = i;
    }
    printf("%c", str[N]);
    return 0;
}