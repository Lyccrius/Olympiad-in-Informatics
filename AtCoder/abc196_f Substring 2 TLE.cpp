#include <iostream>
#include <bitset>
#include <string>

typedef char chr;
typedef std::string str;

const int maxN = 1e6;

str S;
str T;
int n;
int m;
int tag;
int ans = maxN;

int calc(int x, std::bitset<1000000> s, std::bitset<1000000> t) {
    //std::cout << s << '\n';
    //std::cout << t << '\n';
    //std::cout << (t << x) << '\n';
    return (s ^ (t << x)).count();
}

int main() {
    std::cin >> S;
    std::cin >> T;
    std::bitset<1000000> s(S);
    std::bitset<1000000> t(T);
    n = S.size();
    m = T.size();
    //for (int i = 0; i < n; i++) std::cout << s[i]; std::cout << '\n';
    for (int i = m; i < n; i++) if (s[i]) tag++;
    for (int i = 0; i <= n - m; i++) {
        if (i) {
            tag += s[i - 1];
            tag -= s[m + i - 1];
            //printf("- %d, + %d\n", i - 1, n + i);
        }
        int res = calc(i, s, t) - tag;
        //printf("tag = %d\n", tag);
        //printf("res = %d\n", res);
        ans = std::min(ans, res);
    }
    std::cout << ans << '\n';
    return 0;
}