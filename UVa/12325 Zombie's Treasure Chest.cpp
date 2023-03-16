#include <iostream>
#include <algorithm>

typedef long long lxl;

const lxl inf = 1e18 + 10;

int T;
lxl N, S1, V1, S2, V2;

lxl A1() {
    lxl ret = - inf;
    for (lxl i = 0; i * S1 <= N; i++) {
        lxl j = (N - i * S1) / S2;
        ret = std::max(ret, i * V1 + j * V2);
    }
    return ret;
}

lxl A2() {
    lxl ret = - inf;
    for (lxl j = 0; j * S2 <= N; j++) {
        lxl i = (N - j * S2) / S1;
        ret = std::max(ret, i * V1 + j * V2);
    }
    return ret;
}

lxl B1() {
    lxl ret = - inf;
    for (lxl i = 0; i < S2; i++) {
        lxl j = (N - i * S1) / S2;
        ret = std::max(ret, i * V1 + j * V2);
    }
    return ret;
}

lxl B2() {
    lxl ret = - inf;
    for (lxl j = 0; j < S1; j++) {
        lxl i = (N - j * S2) / S1;
        ret = std::max(ret, i * V1 + j * V2);
    }
    return ret;
}

lxl mian() {
    std::cin >> N >> S1 >> V1 >> S2 >> V2;
    if (N / S1 <= 65536) return A1();
    else if (N / S2 <= 65536) return A2();
    else if (S2 * V1 <= S1 * V2) return B1();
    else return B2();
}

int main() {
    std::cin >> T;
    for (int kase = 1; kase <= T; kase++) std::cout << "Case #" << kase << ": " << mian() << '\n';
    return 0;
}