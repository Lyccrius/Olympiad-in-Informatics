#include <iostream>
#include <algorithm>
#include <deque>
#include <set>
#include <map>

typedef std::set<int> sit;
typedef std::map<int, int> mii;

const int maxN = 2e5;
const int maxQ = 2e5;

int n, q;
int s, t, x;
int d;
mii c;

struct Query {
    int t;
    int x;
    int d;

    bool operator<(const Query &other) const {
        return t < other.t;
    }
};

std::deque<Query> query;
sit block;

int main() {
    std::cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> s >> t >> x;
        query.push_back((Query) {s - x, x, 1});
        query.push_back((Query) {t - x, x, 0});
    }
    std::sort(query.begin(), query.end());
    for (int i = 1; i <= q; i++) {
        std::cin >> d;
        while (query.size() && query.front().t <= d) {
            if (query.front().d) {
                if (c[query.front().x] == 0) block.insert(query.front().x);
                c[query.front().x]++;
            } else {
                c[query.front().x]--;
                if (c[query.front().x] == 0) block.erase(query.front().x);
            }
            query.pop_front();
        }
        if (block.size()) {
            std::cout << *block.begin() << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
    return 0;
}