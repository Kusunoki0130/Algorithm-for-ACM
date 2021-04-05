#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 1e4+4;
struct node {
    ll lsum, rsum, msum, sum;
    node () {
        lsum = rsum = msum = sum = 0;
    }
};
node tree[MAXN<<4];
ll a[MAXN];
int n, m, T;

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
node query(int p, int l, int r, int ql, int qr) {
    node ans;
    if (ql<=l && r<=qr) {
        return tree[p];
    }
    int mid = (l+r)>>1;
    if (qr<=mid) {
        ans = query(p<<1, l, mid, ql, qr);
    }
    else if (ql>mid) {
        ans = query(p<<1|1, mid+1, r, ql, qr);
    }
    else {
        node ansl = query(p<<1, l, mid, ql, qr);
        node ansr = query(p<<1|1, mid+1, r, ql ,qr);
        ans.sum = ansl.sum + ansr.sum;
        ans.lsum = max(ansl.lsum, ansl.sum+ansr.lsum);
        ans.rsum = max(ansr.rsum, ansr.sum+ansl.rsum);
        ans.msum = max(max(ansl.msum, ansr.msum), ansl.rsum+ansr.lsum);
        return ans;
    }
}
int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for (int i=1;i<=n;++i) {
            scanf("%lld", &a[i]);
        }
        buildTree(1, 1, n);
        scanf("%d", &m);
        for (int i=1;i<=m;++i) {
            int x1, y1, x2, y2;
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            ll ans = 0;
            if (y1<x2) {
                ll templ = query(1, 1, n, x1, y1).rsum;
                ll tempm = x2-y1>1?query(1, 1, n, y1+1, x2-1).sum:0;
                ll tempr = query(1, 1, n, x2, y2).lsum;
                ans = templ+tempm+tempr;
            }
            else {
                ll temp1 = query(1, 1, n, x2, y1).msum;
                ll temp2 = query(1, 1, n, x1, x2).rsum + query(1, 1, n, x2, y2).lsum - a[x2];
                ll temp3 = query(1, 1, n, x1, y1).rsum + query(1, 1, n, y1, y2).lsum - a[y1];
                ans = max(max(temp1, temp2), temp3);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}