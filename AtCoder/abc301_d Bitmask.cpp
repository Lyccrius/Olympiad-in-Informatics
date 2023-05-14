#include <iostream>
#include <string>

typedef std::string str;
typedef long long lxl;

str s;
lxl n;
lxl ans;

int main(){
    std::cin >> s >> n;
	for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == '1') {
            ans += 1ll << (s.size() - 1 - i);
        }
	}
    for (int i = 0; i <= s.size() - 1; i++) {
        if (s[i] == '?') {
            if (ans + (1ll << (s.size() - 1 - i)) <= n) {
                ans += (1ll << (s.size() - 1 - i));
            }
        }
    }
    if (ans > n) ans = -1;
    std::cout << ans << '\n';
    return 0;
}