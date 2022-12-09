#include <cstdio>
#include <cstring>

const int maxN = 20 + 10;

int n;
char s[maxN];
int div;
int last;

int main() {
    scanf("%s", s + 1);
    n = std::strlen(s + 1);
    div = 1;
    last = 1;
    while (div <= n) {
        while (s[div] >= '0' && s[div] <= '9' && div <= n) div++;
        int div_ = div - 1;
        while (s[div_] == '0' && div_ > last) div_--;
        while (s[last] == '0' && last < div_) last++;
        for (int i = div_; i >= last; i--) printf("%c", s[i]);
        printf("%c", s[div]);
        div++;
        last = div;
    }
    return 0;
}