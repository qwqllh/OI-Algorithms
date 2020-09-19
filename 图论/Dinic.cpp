/**
 * luogu P3254 https://www.luogu.com.cn/problem/P3254
 * Dinic
 **/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int maxn = 1000;
const int S = 0;
const int T = maxn - 1;
const int INF = 0x5f5f5f5f;

struct Edge {
    int to, val, nxt;
}e[maxn * maxn];

int numedge, head[maxn], n, m, depth[maxn], ans, sum;

inline void AddEdge(int from, int to, int val) {
    e[numedge].to = to;
    e[numedge].val = val;
    e[numedge].nxt = head[from];
    head[from] = numedge;
    numedge++;
}

inline void init() {
    memset(head, -1, sizeof(head));
}

inline bool bfs() {
    memset(depth, 0, sizeof(depth));
    depth[S] = 1;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = e[i].nxt) {
            int to = e[i].to;
            if (!depth[to] && e[i].val > 0) {
                depth[to] = depth[u] + 1;
                q.push(to);
            }
        }
    }
    return depth[T] != 0;
}

int dfs(int u, int flow) {
    if (u == T || !flow) return flow;
    int sum = 0;
    for (int i = head[u]; ~i; i = e[i].nxt) {
        int to = e[i].to;
        if (depth[to] > depth[u] && e[i].val > 0) {
            int di = dfs(to, min(flow, e[i].val));
            if (di > 0) {
                sum += di;
                flow -= di;
                e[i].val -= di;
                e[i ^ 1].val += di;
                // return di;
            }
        }
    }
    if (!sum) depth[u] = 0;
    return sum;
}

inline int Dinic() {
    int res = 0;
    while (bfs()) {
        int d;
        while ((d = dfs(S, INF)))
            res += d;
    }
    return res;
}

int main() {
    init();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        sum += x;
        AddEdge(S, i, x);
        AddEdge(i, S, 0);
    }
    for (int i = 1; i <= m; i++) {
        int x;
        scanf("%d", &x);
        AddEdge(i + n, T, x);
        AddEdge(T, i + n, 0);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            AddEdge(i, j + n, 1);
            AddEdge(j + n, i, 0);
        }
    }
    ans = Dinic();
    if (ans == sum) {
        printf("1\n");
        for (int i = 1; i <= n; i++) {
            for (int j = head[i]; ~j; j = e[j].nxt) {
                int to = e[j].to;
                if (to > n && e[j].val == 0) {
                    printf("%d ", to - n);
                }
            }
            putchar('\n');
        }
    }
    else {
        printf("0\n");
    }
    return 0;
}