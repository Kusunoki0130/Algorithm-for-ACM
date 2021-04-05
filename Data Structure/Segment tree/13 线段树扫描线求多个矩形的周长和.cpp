#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 5e3+3;
struct seg {
    ll x1, x2, h;
    int flag;
};
struct node {
    ll sum, tag, num, lc, rc;
    node () {
        sum = tag = num = lc = rc = 0;
    }
};
node tree[MAXN<<4];
seg line[MAXN<<1];
ll x[MAXN<<1];
int cnt;
int len;
int n;
inline seg newLine(ll a, ll b, ll c, int d) {
    seg temp;
    temp.x1 = a, temp.x2 = b, temp.h = c, temp.flag = d;
    return temp;
}
inline int bs(ll k) {
    int l = 0;
    int r = len-1;
    int ret = 0;
    while(l<=r) {
        int mid = (l+r)>>1;
        if (k<x[mid]) {
            r = mid-1;
        }
        else {
            l = mid+1;
            ret = mid;
        }
    }
    return ret;
} 
bool cmp(seg p1, seg p2) {
    return p1.h == p2.h ? p1.flag>p2.flag : p1.h<p2.h;
}

void pushUp(int p, int l, int r) {
    if (tree[p].tag) {
        tree[p].sum = x[r]-x[l-1];
        tree[p].lc = tree[p].rc = 1;
        tree[p].num = 1;
    }
    else if (l==r) {
        tree[p].sum = tree[p].lc = tree[p].rc = tree[p].num = 0;
    }
    else {
        tree[p].sum = tree[p<<1].sum + tree[p<<1|1].sum;
        tree[p].lc = tree[p<<1].lc;
        tree[p].rc = tree[p<<1|1].rc;
        tree[p].num = tree[p<<1].num + tree[p<<1|1].num - (tree[p<<1].rc&tree[p<<1|1].lc);
    }
}
void update(int p, int l, int r, int ql, int qr, int k) {
    if (ql<=l && r<=qr) {
        tree[p].tag += k;
        pushUp(p, l, r);
        return;
    }
    int mid = (l+r)>>1;
    if (ql<=mid) {
        update(p<<1, l, mid, ql, qr, k);
    }
    if (qr>mid) {
        update(p<<1|1, mid+1, r, ql, qr, k);
    }
    pushUp(p, l, r);
}

int main() {
    scanf("%d", &n);
    for (int i=1;i<=n;++i) {
        ll x1, y1, x2, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        x[cnt] = x1;
        line[++cnt] = newLine(x1, x2, y1, 1);
        x[cnt] = x2;
        line[++cnt] = newLine(x1, x2, y2, -1);
    }
    sort(line+1, line+cnt+1, cmp);
    sort(x, x+cnt);
    len = unique(x, x+cnt)-x;
    ll ans = 0;
    ll pre = 0;
    for (int i=1;i<=cnt;++i) {
        int ql = bs(line[i].x1)+1;
        int qr = bs(line[i].x2);
        update(1, 1, len-1, ql, qr, line[i].flag);
        ll temp1 = abs(tree[1].sum-pre);
        ll temp2 = 2 * tree[1].num * (line[i+1].h-line[i].h);
        ans += temp1 + temp2;
        pre = tree[1].sum;
    }
    printf("%lld\n", ans);
    return 0;
}

// 发现一个问题，
// 假如存在两个矩形上下无缝衔接且x轴上长度相等，
// 类似一个“日”字型，
// 对扫描线排序的时候需要把上矩形下边排到下矩形上边的前面。
// 否则，算法会认为这两个矩形是上下分开的。