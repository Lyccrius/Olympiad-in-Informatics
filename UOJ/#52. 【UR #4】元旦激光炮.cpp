#include "kth.h"
#include <vector>
#include <algorithm>

typedef std::vector<int> vic;

#ifndef ONLINE_JUDGE
    /* This is sample grader for the contestant */
    #include "kth.h"
    #include <stdio.h>
    #include <assert.h>

    #define MaxN 100000
    #define INF 2147483647

    static int a_n, b_n, c_n;
    static int a[MaxN];
    static int b[MaxN];
    static int c[MaxN];

    static int tot_get;

    int get_a(int p)
    {
        tot_get++;
        if (0 <= p && p < a_n)
            return a[p];
        return INF;
    }
    int get_b(int p)
    {
        tot_get++;
        if (0 <= p && p < b_n)
            return b[p];
        return INF;
    }
    int get_c(int p)
    {
        tot_get++;
        if (0 <= p && p < c_n)
            return c[p];
        return INF;
    }

    int main()
    {
        int i;
        int res, k;

        assert(scanf("%d %d %d %d", &a_n, &b_n, &c_n, &k) == 4);
        for (i = 0; i < a_n; i++)
            assert(scanf("%d", &a[i]) == 1);
        for (i = 0; i < b_n; i++)
            assert(scanf("%d", &b[i]) == 1);
        for (i = 0; i < c_n; i++)
            assert(scanf("%d", &c[i]) == 1);

        tot_get = 0;
        res = query_kth(a_n, b_n, c_n, k);
        printf("%d %d\n", res, tot_get);

        return 0;
    }
#endif

int query_kth(int n_a, int n_b, int n_c, int k) {
    int l_a = 0;
    int l_b = 0;
    int l_c = 0;
    while (k > 2) {
        int l = k / 3;
        int minv = 2147483647;
        int minp = 0;
        int al = get_a(l_a + l - 1);
        int bl = get_b(l_b + l - 1);
        int cl = get_c(l_c + l - 1);
        if (minv > al) minv = al, minp = 1;
        if (minv > bl) minv = bl, minp = 2;
        if (minv > cl) minv = cl, minp = 3;
        if (minp == 1) l_a += l;
        if (minp == 2) l_b += l;
        if (minp == 3) l_c += l;
        k -= l;
    }
    vic a;
    a.push_back(get_a(l_a));
    a.push_back(get_a(l_a + 1));
    a.push_back(get_b(l_b));
    a.push_back(get_b(l_b + 1));
    a.push_back(get_c(l_c));
    a.push_back(get_c(l_c + 1));
    std::sort(a.begin(), a.end());
    return a[k - 1];
}