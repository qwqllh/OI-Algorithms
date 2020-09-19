/**
 * 倍增法
 * https://www.luogu.com.cn/problem/P3379
 * 洛谷 P3379 【模板】最近公共祖先（LCA）
 **/

#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 5e5 + 5;

struct Edge {
    int to, val, nxt;
}e[maxn << 1];
int head[maxn], numedge, n, m, s, fa[30][maxn], depth[maxn], lg[maxn], x, y;

inline void AddEdge(int from, int to) {
    numedge++;
    e[numedge].to = to;
    e[numedge].nxt = head[from];
    head[from] = numedge;
}

void dfs(int u, int f) {
    fa[0][u] = f;
    depth[u] = depth[f] + 1;
    for (int i = 1; i <= lg[depth[u]]; i++) {
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    }

    for (int i = head[u]; i; i = e[i].nxt) {
        int to = e[i].to; if (to == f) continue;
        dfs(to, u);
    }
}

int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    while (depth[x] > depth[y])
        x = fa[lg[depth[x] - depth[y]]][x];
    
    if (x == y) return x;
    for (int i = lg[depth[x]]; i >= 0; i--) {
        if (fa[i][x] == fa[i][y]) continue;
        x = fa[i][x]; y = fa[i][y];
    }
    return fa[0][x];
}

int main() {
    scanf("%d%d%d", &n, &m, &s);
    for (int i = 2; i <= n; i++)
        lg[i] = lg[i >> 1] + 1;

    for (int i = 1; i < n; i++) {
        scanf("%d%d", &x, &y);
        AddEdge(x, y);
        AddEdge(y, x);
    }
    dfs(s, s);

    for (int i = 0; i < m; i++) {
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
    return 0;
}