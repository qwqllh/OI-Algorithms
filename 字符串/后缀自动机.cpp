/**
 * 出处:https://www.luogu.com.cn/blog/Kesdiael3/hou-zhui-zi-dong-ji-yang-xie
 **/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;
const int maxn = 10005;

struct Node {
    int ch[26];
    int len, fa;
    Node() {
        memset(ch, 0, sizeof(ch));
        len = 0;
    }
}dian[maxn << 1];

int las = 1, tot = 1;
void add(int c) {
    int p = las;
    int np = las = ++tot;
    dian[np].len = dian[p].len + 1;
    for ( ; p && !dian[p].ch[c]; p = dian[p].fa) dian[p].ch[c] = np;
    
    if(!p) dian[np].fa = 1;
    else {
        int q = dian[p].ch[c];
        if (dian[q].len == dian[p].len + 1) dian[np].fa = q;
        else {
            int nq = ++tot;
            dian[nq] = dian[q];
            dian[nq].len = dian[p].len + 1;
            dian[q].fa = dian[np].fa = nq;
            for ( ; p && dian[p].ch[c] == q; p = dian[p].fa) dian[p].ch[c] = nq;
        }
    }
}

