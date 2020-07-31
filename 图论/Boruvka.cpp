/**
 * Problem: https://codeforces.com/contest/888/problem/G
 **/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define maxn 200005
#define FUCK printf("---FUUUUUUUCK!!!---\n");
#define NUMBIT 29
typedef long long ll;
using namespace std;

inline void readll(int &x) {
    x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') {
        x = x * 10 - '0' + ch;
        ch = getchar();
    }
}

int n, a[maxn], fa[maxn], refroot[maxn], mnto[maxn], mnval[maxn];
vector<int> son[maxn];

// 并查集
int getfa(int x) {
    if (fa[x] != x) fa[x] = getfa(fa[x]);
    return fa[x];
}

bool Merge(int a, int b) {
    int faa = getfa(a), fab = getfa(b);
    if (faa == fab) return false;
    fa[faa] = fab;
    return true;
}

// Trie
int ch[2][maxn * 33], siz[maxn * 33], id[maxn * 33], tot;

void modify(int num, int val, int ID) {
    int u = 0;
    for (int i = NUMBIT; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (!ch[bit][u])
            ch[bit][u] = ++tot;
        u = ch[bit][u];
        siz[u] += val;
    }
    id[u] = ID;
}

int query(int num) {
    int u = 0;
    for (int i = NUMBIT; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (siz[ch[bit][u]]) u = ch[bit][u];
        else u = ch[!bit][u];
    }
    return id[u];
}

void init() {
    for (int i = 0; i <= n; i++) fa[i] = i;
}

int main() {
    readll(n);
    init();

    for (int i = 1; i <= n; i++) readll(a[i]);
    
    sort(a + 1, a + n + 1);
    a[0] = -1;

    for (int i = 1; i <= n; i++) {
        modify(a[i], 1, i);
        if (a[i] == a[i - 1]) {
            Merge(i, i - 1);
        }
    }

    ll ans = 0;
    while (true) {
        // FUCK
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (fa[i] == i) {
                refroot[i] = ++cnt;
                mnto[cnt] = -1;
                mnval[cnt] = -1;
            }
        }

        if (cnt == 1) break;
        for (int i = 1; i <= n; i++) {
            son[refroot[getfa(i)]].push_back(i);
        }

        for (int i = 1; i <= cnt; i++) {
            for (int j = 0; j < (int)son[i].size(); j++) {
                int u = son[i][j];
                modify(a[u], -1, u);
            }

            for (int j = 0; j < (int)son[i].size(); j++) {
                int u = son[i][j];
                int resu = query(a[u]);

                // printf("u = %d, resu = %d\n", u, resu);

                if (mnval[i] == -1 || mnval[i] > (a[u] ^ a[resu])) {
                    mnval[i] = (a[u] ^ a[resu]);
                    mnto[i] = resu;
                }
            }

            for (int j = 0; j < (int)son[i].size(); j++) {
                int u = son[i][j];
                modify(a[u], 1, u);
            }
            son[i].clear();
        }

        for (int i = 1; i <= n; i++) {
            if (fa[i] == i && Merge(i, mnto[refroot[i]])) {
                ans += mnval[refroot[i]];
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}