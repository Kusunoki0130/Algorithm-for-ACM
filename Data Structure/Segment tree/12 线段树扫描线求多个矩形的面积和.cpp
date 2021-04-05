#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;
struct seg {
    ll x1, x2, h;
    int flag;
};
seg line[MAXN<<1];
ll x[MAXN<<1];
ll tree[MAXN<<4];
ll tag[MAXN<<4];
int n;
int cnt;
int len;
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
    return p1.h<p2.h;
}

void pushUp(int p, int l, int r) {
    if (tag[p]) {
        tree[p] = x[r]-x[l-1];
    }
    else if (l==r) {
        tree[p] = 0;
    }
    else {
        tree[p] = tree[p<<1] + tree[p<<1|1];
    }
}
void update(int p, int l, int r, int ql, int qr, int k) {
    if (ql<=l && r<=qr) {
        tag[p] += k;
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
        ll x1, x2, y1, y2;
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
    for (int i=1;i<cnt;++i) {
        int ql = bs(line[i].x1)+1;
        int qr = bs(line[i].x2);
        update(1, 1, len-1, ql, qr, line[i].flag);
        ans += (line[i+1].h-line[i].h)*tree[1];
    }
    printf("%lld\n", ans);
    return 0;
}