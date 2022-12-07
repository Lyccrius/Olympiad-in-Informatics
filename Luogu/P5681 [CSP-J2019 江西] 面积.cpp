#include <cstdio>

long long a, b, c;

int main() {
    scanf("%lld%lld%lld", &a, &b, &c);
    if (a * a > b * c) printf("Alice\n");
    else printf("Bob\n");
    return 0;
}