#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

void promote() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
    return;
}

const int maxN = 1000;

int n;
int a[maxN + 10];
std::stack<int> s1, s2;
std::vector<char> ans;
int cur = 1;

namespace graph {
    struct Vertex {
        int head;
        int vis;
        int col;
    } vertex[maxN + 10];

    struct Edge {
        int head;
        int next;
    } edge[maxN * maxN + 10];

    int ecnt;

    void addEdge(int tail, int head) {
        ecnt++;
        edge[ecnt].head = head;
        edge[ecnt].next = vertex[tail].head;
        vertex[tail].head = ecnt;
        return;
    }

    bool DFS(int u, int col) {
        vertex[u].vis = true;
        vertex[u].col = col;
        for (int e = vertex[u].head; e; e = edge[e].next) {
            int v = edge[e].head;
            if (vertex[v].vis) {
                if (vertex[u].col == vertex[v].col) {
                    return false;
                }
            } else {
                if (!DFS(v, 3 - col)) {
                    return false;
                }
            }
        }
        return true;
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) std::cin >> a[i]; int m = a[n];
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 1; j < i; j++) {
            if (m < a[j] && a[j] < a[i]) {
                graph::addEdge(i, j);
                graph::addEdge(j, i);
            }
        }
        m = std::min(m, a[i]);
    }
    for (int i = 1; i <= n; i++) {
        if (!graph::vertex[i].vis) {
            if (!graph::DFS(i, 1)) {
                std::cout << 0 << '\n';
                return 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
    	if (graph::vertex[i].col == 1) {
            s1.push(a[i]);
            ans.push_back('a');
        } else {
            s2.push(a[i]);
            ans.push_back('c');
        }
        while (!s1.empty() && s1.top() == cur || !s2.empty() && s2.top() == cur)
	        if (!s1.empty() && s1.top() == cur) {
	            s1.pop();
                ans.push_back('b');
	            cur++;
	        } else {
	            s2.pop();
                ans.push_back('d');
	            cur++;
	        }
    }
    for (int j = ans.size() - 1; j >= 0; j--) {
        for (int i = 0; i < ans.size() - 1; i++) {
            if (ans[i] == 'c' && ans[i + 1] == 'b') std::swap(ans[i], ans[i + 1]);
            if (ans[i] == 'd' && ans[i + 1] == 'a') std::swap(ans[i], ans[i + 1]);
        }
    }
    for (auto ch : ans) std::cout << ch << ' ';
    return 0;
}