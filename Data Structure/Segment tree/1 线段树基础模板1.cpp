#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;
ll tree[MAXN<<4];
ll tag[MAXN<<4];
ll a[MAXN];
int n, m;

inline void pushUp(int p) {
    tree[p] = tree[p<<1] + tree[p<<1|1];
}
inline void pushDown(int l, int r, int p) {
    int mid = (l+r)>>1;
    tree[p<<1] += (mid-l+1) * tag[p];
    tree[p<<1|1] += (r-mid) * tag[p];
    tag[p<<1] += tag[p];
    tag[p<<1|1] += tag[p];
    tag[p] = 0; 
}

void buildTree(int l, int r, int p) {
    tag[p] = 0;
    if (l==r) {
        tree[p] = a[l];
        return ;
    }
    int mid = (l+r)>>1;
    buildTree(l, mid, p<<1);
    buildTree(mid+1, r, p<<1|1);
    pushUp(p);
}

void update(int l, int r, int ql, int qr, int p, ll k) {
    if (ql<=l && r<=qr) {
        tree[p] += (r-l+1)*k;
        tag[p] += k;
        return;
    }
    pushDown(l, r, p);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        update(l, mid, ql, qr, p<<1, k);
    }
    if (qr>mid) {
        update(mid+1, r, ql, qr, p<<1|1, k);
    }
    pushUp(p);
}

ll query(int l, int r, int ql, int qr, int p) {
    ll ans = 0;
    if (ql<=l && r<=qr) {
        return tree[p];
    }
    pushDown(l, r, p);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        ans += query(l, mid, ql, qr, p<<1);
    }
    if (qr>mid) {
        ans += query(mid+1, r, ql, qr, p<<1|1);
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i=1;i<=n;++i) {
        scanf("%lld", &a[i]);
    }
    buildTree(1, n, 1);
    for (int i=0;i<m;++i) {
        int num, x, y;
        scanf("%d %d %d", &num, &x, &y);
        if (num==1) {
            ll k;
            scanf("%lld", &k);
            update(1, n, x, y, 1, k);
        }
        else {
            printf("%lld\n", query(1, n, x, y, 1));
        }
    }
    return 0;
}