#include <iostream>
#include <deque>
#include <map>

typedef unsigned long long ull;
typedef std::deque<int> diq;
typedef std::deque<ull> duq;
typedef std::map<ull, int> mui;

const int maxN = 100;
const int maxM = 100;
const int base = 227;
const int bigp = 19260817;
const int mod = 998244353;

int n, m;
int a[maxN + 10];
int b[maxN + 10];
mui f;

struct State {
    struct Tower {
        diq t;
        duq h;

        ull hash() {
            if (h.empty()) return 0;
            return h.back();
        }

        void clear() {
            t.clear();
            h.clear();
            return;
        }

        void push(int x) {
            t.push_back(x);
            h.push_back(hash() * base + x);
            return;
        }

        void pop() {
            t.pop_back();
            h.pop_back();
            return;
        }

        int top() {
            return t.back();
        }

        bool empty() {
            return t.empty();
        }
    } t[5];

    void push(int i, int x) {
        t[i].push(x);
        return;
    }

    ull hash() {
        return t[1].hash() * bigp * bigp + t[2].hash() * bigp + t[3].hash();
    }
} s, t;

int DFS(State s, int step) {
    if (f.count(s.hash() * base + step)) return f[s.hash() * base + step];
    int ret = (s.hash() == t.hash());
    if (!step) return f[s.hash() * base + step] = ret;
    for (int i = 1; i <= 3; i++) {
        if (s.t[i].empty()) continue;
        for (int j = 1; j <= 3; j++) {
            if (i == j) continue;
            if (!s.t[j].empty() && s.t[i].top() > s.t[j].top()) continue;
            s.t[j].push(s.t[i].top());
            s.t[i].pop();
            ret = (ret + DFS(s, step - 1)) % mod;
            s.t[i].push(s.t[j].top());
            s.t[j].pop();
        }
    }
    return f[s.hash() * base + step] = ret;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= n; i++) std::cin >> b[i];
    for (int i = n; i >= 1; i--) s.push(a[i], i);
    for (int i = n; i >= 1; i--) t.push(b[i], i);
    std::cout << DFS(s, m) << '\n';
    return 0;
}