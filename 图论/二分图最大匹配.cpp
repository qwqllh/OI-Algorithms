/**
 * 匈牙利算法
 * 二分图最大匹配
 * https://www.luogu.com.cn/problem/P3386
 **/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1005;
const int maxm = 1e5 + 5;

int n, m, t, ans;
int match[maxn], vis[maxn];
struct Edge {
    int to, nxt;
}e[maxm];
int numedge, head[maxn];

inline void AddEdge(int from, int to) {
    e[numedge].to = to;
    e[numedge].nxt = head[from];
    head[from] = numedge;
    numedge++;
}

int dfs(int u, int tag) {
    if (vis[u] == tag) return false;
    vis[u] = tag;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int to = e[i].to;
        if (!match[to] || dfs(match[to], tag)) {
            match[to] = u;
            return true;
        }
    }
    return false;
}

int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d%d", &n, &t, &m);
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        y += n;
        AddEdge(x, y);
        AddEdge(y, x);
    }
    t += n;
    for (int i = 1; i <= n; i++) {
        if (dfs(i, i))
            ans++;
    }
    printf("%d\n", ans);
    return 0;
}