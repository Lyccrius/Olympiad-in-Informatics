#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

const int maxC = 2500;
const int maxL = 2500;
const int maxSPFi = 1000;

int C, L;

struct Cow {
    int minSPF;
    int maxSPF;

    bool operator<(const Cow &other) const {
        return maxSPF > other.maxSPF;
    }
} cow[maxC + 10];

struct Cream {
    int SPF;
    int cover;
} cre[maxL + 10];

bool cmpByMinSPF(const Cow &a, const Cow &b) {
    return a.minSPF < b.minSPF;
}

bool cmpBySPF(const Cream &a, const Cream &b) {
    return a.SPF < b.SPF;
}

int ans = 0;

int main() {
    std::cin >> C >> L;
    for (int i = 1; i <= C; i++) std::cin >> cow[i].minSPF >> cow[i].maxSPF;
    for (int i = 1; i <= L; i++) std::cin >> cre[i].SPF >> cre[i].cover;
    std::sort(cow + 1, cow + C + 1, cmpByMinSPF);
    std::sort(cre + 1, cre + L + 1, cmpBySPF);
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    for (int i = 1, j = 1; i <= L; i++) {
        while (j <= C && cow[j].minSPF <= cre[i].SPF) q.push(cow[j].maxSPF), j++;
        while (!q.empty() && cre[i].cover) {
            int c = q.top();
            q.pop();
            if (cre[i].SPF <= c) {
                cre[i].cover--;
                ans++;
            }
        }
    }
    std::cout << ans;
    return 0;
}