#include <iostream>
#include <queue>
#include <vector>

const int maxN = 1e5;
const int maxP = 5e5;

int n, k, p;
int a[maxP + 10];
int inq[maxN + 10];
int last[maxP + 10];
int next[maxP + 10];
int ans;

struct cmp {
    bool operator()(const int &x, const int &y) {
        return next[x] < next[y];
    }
};

std::priority_queue<int, std::vector<int>, cmp> q;

int main() {
    std::cin >> n >> k >> p;
    for (int i = 1; i <= p; i++) std::cin >> a[i];
    for (int i = 1; i <= p; i++) {
        next[last[a[i]]] = i;
        last[a[i]] = i;
        next[i] = p + 1;
    }
    for (int i = 1; i <= p; i++) {
        if (inq[a[i]]) {
            q.push(i);
            k++;
        } else {
            if (q.size() == k) {
                inq[a[q.top()]] = false;
                q.pop();
            }
            inq[a[i]] = true;
            q.push(i);
            ans++;
        }
    }
    std::cout << ans;
    return 0;
}