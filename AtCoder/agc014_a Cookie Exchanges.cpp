#include <iostream>

int A, B, C;
int cnt;

int main() {
    std::cin >> A >> B >> C;
    while (((A & 1) == 0) && ((B & 1) == 0) && ((C & 1) == 0)) {
        if (A == B && B == C) {
            std::cout << -1;
            return 0;
        }
        int a = A;
        int b = B;
        int c = C;
        A = (b + c) / 2;
        B = (a + c) / 2;
        C = (a + b) / 2;
        cnt++;
    }
    std::cout << cnt;
    return 0;
}