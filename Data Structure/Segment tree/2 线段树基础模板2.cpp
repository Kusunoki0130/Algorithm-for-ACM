#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;
ll tree[MAXN<<4];
ll tagAdd[MAXN<<4];
ll tagMul[MAXN<<4];
ll a[MAXN];
int n, m;
int mod;

inline void pushUp(int p) {
    tree[p] = (tree[p<<1] + tree[p<<1|1])%mod;
}
inline void pushDown(int p, int l, int r) {
    int mid = (l+r)>>1;
    tree[p<<1] = ((tree[p<<1]*tagMul[p])%mod + ((mid-l+1)*tagAdd[p])%mod)%mod;
    tree[p<<1|1] = ((tree[p<<1|1]*tagMul[p])%mod + ((r-mid)*tagAdd[p])%mod)%mod;
    tagMul[p<<1] = (tagMul[p<<1]*tagMul[p])%mod;
    tagMul[p<<1|1] = (tagMul[p<<1|1]*tagMul[p])%mod;
    tagAdd[p<<1] = ((tagAdd[p<<1]*tagMul[p])%mod + tagAdd[p])%mod;
    tagAdd[p<<1|1] = ((tagAdd[p<<1|1]*tagMul[p])%mod + tagAdd[p])%mod;
    tagAdd[p] = 0;
    tagMul[p] = 1;
}

void buildTree(int p, int l, int r) {
    tagAdd[p] = 0;
    tagMul[p] = 1;
    if (l==r) {
        tree[p] = a[l]%mod;
        return;
    }
    int mid = (l+r)>>1;
    buildTree(p<<1, l, mid);
    buildTree(p<<1|1, mid+1, r);
    pushUp(p);
}

void updateAdd(int p, int l, int r, int ql, int qr, ll k) {
    if (ql<=l && r<=qr) {
        tree[p] += ((r-l+1)%mod)*k%mod;
        tree[p] %= mod;
        tagAdd[p] += k;
        tagAdd[p] %= mod;
        return; 
    }
    pushDown(p, l ,r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        updateAdd(p<<1, l, mid, ql, qr, k);
    }
    if (qr>mid) {
        updateAdd(p<<1|1, mid+1, r, ql, qr, k);
    }
    pushUp(p);
    return;
}

void updateMul(int p, int l, int r, int ql, int qr, ll k) {
    if (ql<=l && r<= qr) {
        tree[p] = (tree[p]*k)%mod;
        tagMul[p] = (tagMul[p]*k)%mod;
        tagAdd[p] = (tagAdd[p]*k)%mod;
        return;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        updateMul(p<<1, l, mid, ql, qr, k);
    }
    if (qr>mid) {
        updateMul(p<<1|1, mid+1, r, ql, qr, k);
    }
    pushUp(p);
    return;
}

ll query(int p, int l, int r, int ql, int qr) {
    ll ans = 0;
    if (ql<=l && r<=qr) {
        return tree[p];
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        ans += query(p<<1, l, mid, ql, qr);
        ans %= mod;
    }
    if (qr>mid) {
        ans += query(p<<1|1, mid+1, r, ql, qr);
        ans %= mod;
    }
    return ans;
}

int main() {
    scanf("%d %d %d", &n, &m, &mod);
    for (int i=1;i<=n;++i) {
        scanf("%lld", &a[i]);
    }
    buildTree(1, 1, n);
    for (int i=0;i<m;++i) {
        int num, x, y;
        scanf("%d %d %d", &num, &x, &y);
        if (num==1) {
            ll k;
            scanf("%lld", &k);
            updateMul(1, 1, n, x, y, k%mod);
        }
        else if (num==2) {
            ll k;
            scanf("%lld", &k);
            updateAdd(1, 1, n, x, y, k%mod);
        }
        else {
            printf("%lld\n", query(1, 1, n, x, y));
        }
    }
    return 0;
}