#include <cstdio>
#include <cstring>

const int maxn = 5e4 + 10;

struct HashMap {
    struct Edge {
        long long key;
        int value;
        int next;
    };

    Edge data[maxn << 1];
    int head[maxn];
    int cnt;

    HashMap() {
        cnt = 0;
        std::memset(head, 0, sizeof(head));
    }

    void clear() {
        cnt = 0;
        memset(head, 0, sizeof(head));
        return;
    }

    int hash(long long key) {
        return (key % maxn + maxn) % maxn;
    }

    int& operator [](long long key) {
        int h = hash(key);
        for (int i = head[h]; i; i = data[i].next) {
            if (data[i].key == key) {
                return data[i].value;
            }
        }
        data[++cnt] = (Edge){key, -1, head[h]};
        head[h] = cnt;
        return data[cnt].value;
    }
};

int T;

int n;
int array[maxn];

HashMap hash;

int main() {
	scanf("%d", &T);
	while (T--) {
		hash.clear();
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &array[i]);
			if (hash[array[i]] == -1) {
				hash[array[i]] = i;
				printf("%d ", array[i]);
			}
		}

		printf("\n");
	}

	return 0;
}