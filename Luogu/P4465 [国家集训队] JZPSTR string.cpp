#include <iostream>
#include <bitset>
#include <string>
#include <cstring>

typedef char chr;
typedef std::string str;

const int maxN = 1e6;

int T;
int p;
int n;
int x, y;
chr z[maxN + 10];
str s;

void add() {
    std::cin >> x >> z;
    s.insert(x, z);
    return;
}

void del() {
    std::cin >> x >> y;
    s.erase(x, y - x);
    return;
}

int ShiftAnd() {
    int ret = 0;
    std::bitset<maxN + 10> a[10];
    std::bitset<maxN + 10> t;
    int n = strlen(z);
    for (int i = 0; i < 10; i++) a[i].reset(); t.reset();
    for (int i = 0; z[i]; i++) a[z[i] - '0'][i] = true;
    std::string::iterator it = s.begin() + x;
    std::bitset<maxN + 10> sum;
    sum.reset();
    sum.flip();
    for (int i = y - x; i; i--) {
        //t = ((t << 1) ^ 1) & (a[*it] - '0');
        t = t << 1;
        t[0] = true;
        t = t & (a[*it - '0']);
        if ((t & sum)[n]) ret++;
        it++;
    }
    return ret;
}

void qry() {
    std::cin >> x >> y >> z;
    std::cout << ShiftAnd() << '\n';
    return;
}

void mian() {
    std::cin >> p;
    if (p == 0) add();
    else if (p == 1) del();
    else if (p == 2) qry();
    return;
}

int main() {
    std::cin >> T;
    while (T--) mian();
    return 0;
}