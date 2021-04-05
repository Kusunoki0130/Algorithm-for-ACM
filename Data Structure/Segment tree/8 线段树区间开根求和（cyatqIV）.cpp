#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;
ll tree[MAXN<<4];
ll a[MAXN];
int n, m;

inline void pushUp(int p) {
    tree[p] = tree[p<<1] + tree[p<<1|1];
}
void buildTree(int p, int l, int r) {
    if (l==r) {
        tree[p] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    buildTree(p<<1, l, mid);
    buildTree(p<<1|1, mid+1, r);
    pushUp(p);
}
void update(int p, int l, int r, int ql, int qr) {
    if (ql<=l && r<=qr && l==r) {
        tree[p] = (ll)sqrt((double)tree[p]);
        return;
    }
    int mid = (l+r)>>1;
    if (ql<=mid && tree[p<<1]!=mid-l+1) {
        update(p<<1, l, mid, ql, qr);
    }
    if (qr>mid && tree[p<<1|1]!=r-mid) {
        update(p<<1|1, mid+1, r, ql, qr);
    }
    pushUp(p);
}
ll query(int p, int l, int r, int ql, int qr) {
    ll ans = 0;
    if (ql<=l && r<=qr) {
        return tree[p];
    }
    int mid = (l+r)>>1;
    if (ql<=mid) {
        ans += query(p<<1, l, mid, ql, qr);
    }
    if (qr>mid) {
        ans += query(p<<1|1, mid+1, r, ql, qr);
    }
    return ans;
}

int main() {
    int cnt = 0;
    while(~scanf("%d", &n)) {
        for (int i=1;i<=n;++i) {
            scanf("%lld", &a[i]);
        }
        buildTree(1, 1, n);
        scanf("%d", &m);
        printf("Case #%d:\n", ++cnt);
        for (int i=1;i<=m;++i) {
            int opt, x, y;
            scanf("%d %d %d", &opt, &x, &y);
            if (x>y) {
                swap(x, y);
            }
            if (opt==0) {
                update(1, 1, n, x, y);
            }
            else {
                printf("%lld\n", query(1, 1, n, x, y));
            }
        }
    }
    return 0;
}