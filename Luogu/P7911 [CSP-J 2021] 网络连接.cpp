#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <map>

int n;
std::string op, ad;
std::map<std::string, int> connect;

bool check(std::string s) {
    int a, b, c, d, e;
    if (sscanf(s.c_str(), "%d.%d.%d.%d:%d", &a, &b, &c, &d, &e) != 5) return false;
    if (a < 0 || a > 255 || b < 0 || b > 255 || c < 0 || c > 255 || d < 0 || d > 255 || e < 0 || e > 65535)  return false;
    std::stringstream ss;
    ss << a << '.' << b << '.' << c << '.' << d << ':' << e;
    return ss.str() == s;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        std::cin >> op >> ad;
        if (!check(ad)) {
            printf("ERR\n");
            continue;
        }
        if (op[0] == 'S') {
            if (connect[ad]) printf("FAIL\n");
            else connect[ad] = i, printf("OK\n");
        } else {
            if (!connect.count(ad)) printf("FAIL\n");
            else printf("%d\n", connect[ad]);
        }
    }
    return 0;
}