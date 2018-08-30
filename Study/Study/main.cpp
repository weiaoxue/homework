#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int a[20], sumb[3], res[20];

bool cmp(int aa, int bb) {
    return aa > bb;
}

int main() {
    //freopen("C-small-attempt1.in.txt", "r", stdin);
    //freopen("C-small-attempt1.out.txt", "w", stdout);
    int t, n, i, j, b, cas = 1, cnt, sum, num, ans, count;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (i = 0; i < n * 3; ++i)
            scanf("%d", &a[i]);
        for (i = 0; i < 3; ++i) {
            sumb[i] = 0;
            for (j = 0; j < n; ++j) {
                scanf("%d", &b);
                sumb[i] += b;
            }
        }
        sort(a, a + n * 3, cmp);
        cnt = 0;
        ans = 0;
        count = 0;
        for (i = 0; i < n; ++i) {
            res[i] = a[cnt++];
            res[i + n] = a[cnt++];
        }
        for (i = 0; i < n; ++i)
            res[n * 2 + i] = a[cnt++];
//        for (i = 0 ; i < n * 3; ++i)
//            cout << res[i] << " ";
//        cout << endl;
        num = 0;
        for (i = 0; i < 3; ++i) {
            sum = 0;
            for (j = 0; j < n; ++j) {
                sum += res[i * 3 + j];
            }
            if (sum > sumb[i]) num++;
        }
        if (num > 1) ans++;
        count++;
        cnt = 0;
        for (i = 0; i < n; ++i) {
            res[i] = a[cnt++];
            res[i + n * 2] = a[cnt++];
        }
        for (i = 0; i < n; ++i)
            res[n + i] = a[cnt++];
        num = 0;
        for (i = 0; i < 3; ++i) {
            sum = 0;
            for (j = 0; j < n; ++j) {
                sum += res[i * 3 + j];
            }
            if (sum > sumb[i]) num++;
        }
        if (num > 1) ans++;
        count++;
        cnt = 0;
        for (i = 0; i < n; ++i) {
            res[i + n] = a[cnt++];
            res[i + n * 2] = a[cnt++];
        }
        for (i = 0; i < n; ++i)
            res[i] = a[cnt++];
        num = 0;
        for (i = 0; i < 3; ++i) {
            sum = 0;
            for (j = 0; j < n; ++j) {
                sum += res[i * 3 + j];
            }
            if (sum > sumb[i]) num++;
        }
        if (num > 1) ans++;
        count++;
        printf("Case #%d: %.9f\n", cas++, ans * 1.0 / count);
    }
    return 0;
}
