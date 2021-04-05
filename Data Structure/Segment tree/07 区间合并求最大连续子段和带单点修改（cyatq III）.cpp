#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 5e4+4;
struct node {
    ll lsum, rsum, msum, sum;
    node () {
        lsum = rsum = msum = sum = 0;
    }
};
node tree[MAXN<<4];
ll a[MAXN];
int n, m;

inline void pushUp(int p) {
    tree[p].sum = tree[p<<1].sum + tree[p<<1|1].sum;
    tree[p].lsum = max(tree[p<<1].lsum, tree[p<<1].sum+tree[p<<1|1].lsum);
    tree[p].rsum = max(tree[p<<1|1].rsum, tree[p<<1|1].sum+tree[p<<1].rsum);
    tree[p].msum = max(max(tree[p<<1].msum, tree[p<<1|1].msum), tree[p<<1].rsum+tree[p<<1|1].lsum);
}
void buildTree(int p, int l, int r) {
    if (l==r) {
        tree[p].lsum = tree[p].rsum = tree[p].msum = tree[p].sum = a[l];
        return;
    }
    int mid = (l+r)>>1;
    buildTree(p<<1, l, mid);
    buildTree(p<<1|1, mid+1, r);
    pushUp(p);
}
void update(int p, int l, int r, int pos, ll k) {
    if (l==r&&l==pos) {
        tree[p].lsum = tree[p].rsum = tree[p].msum = tree[p].sum = k;
        return;
    }
    int mid = (l+r)>>1;
    if (pos<=mid) {
        update(p<<1, l, mid, pos, k);
    }
    else {
        update(p<<1|1, mid+1, r, pos, k);
    }
    pushUp(p);
}
node query(int p, int l, int r, int ql, int qr) {
    node ans;
    if (ql<=l && r<=qr) {
        return tree[p];
    }
    int mid = (l+r)>>1;
    if (qr<=mid) {
        ans = query(p<<1, l, mid, ql, qr);
    }
    if (ql>mid) {
        ans = query(p<<1|1, mid+1, r, ql, qr);
    }
    if (ql<=mid && qr>mid) {
        node ansl = query(p<<1, l, mid, ql, qr);
        node ansr = query(p<<1|1, mid+1, r, ql ,qr);
        ans.sum = ansl.sum + ansr.sum;
        ans.lsum = max(ansl.lsum, ansl.sum+ansr.lsum);
        ans.rsum = max(ansr.rsum, ansr.sum+ansl.rsum);
        ans.msum = max(max(ansl.msum, ansr.msum), ansl.rsum+ansr.lsum);
    }
    return ans;
}

int main() {
    scanf("%d", &n);
    for (int i=1;i<=n;++i) {
        scanf("%lld", &a[i]);
    }
    buildTree(1, 1, n);
    scanf("%d", &m);
    for (int i=1;i<=m;++i) {
        int opt, x, y;
        scanf("%d %d %d", &opt, &x, &y);
        if (opt==0) {
            update(1, 1, n, x, y);
        }
        else {
            printf("%lld\n", (query(1, 1, n, x, y)).msum);
        }
    }
    return 0;
}