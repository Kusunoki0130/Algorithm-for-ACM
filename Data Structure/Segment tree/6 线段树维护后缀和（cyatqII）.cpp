#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 1e5+5;
struct node {
    ll sum, msum, tag1, tag2;
    node () {
        sum = msum = tag1 = tag2 = 0;
    }
};
struct que {
    int ql, qr, qpos;
};
node tree[MAXN<<4];
ll a[MAXN];
que q[MAXN];
int pos[MAXN<<2];
int pre[MAXN];
ll ans[MAXN];
int n, m;

bool cmp(que p1, que p2) {
    return p1.qr<p2.qr;
}

inline void pushUp(int p) {
    tree[p].sum = max(tree[p<<1].sum, tree[p<<1|1].sum);
    tree[p].msum = max(tree[p<<1].msum, tree[p<<1|1].msum);
}
inline void pushDown(int p, int l, int r) {
    tree[p<<1].msum = max(tree[p<<1].msum, tree[p<<1].sum+tree[p].tag2);
    tree[p<<1|1].msum = max(tree[p<<1|1].msum, tree[p<<1|1].sum+tree[p].tag2);
    tree[p<<1].sum += tree[p].tag1;
    tree[p<<1|1].sum += tree[p].tag1;
    tree[p<<1].tag2 = max(tree[p<<1].tag2, tree[p<<1].tag1+tree[p].tag2);
    tree[p<<1|1].tag2 = max(tree[p<<1|1].tag2, tree[p<<1|1].tag1+tree[p].tag2);
    tree[p<<1].tag1 += tree[p].tag1;
    tree[p<<1|1].tag1 += tree[p].tag1;
    tree[p].tag1 = 0;
    tree[p].tag2 = 0;
}
void update(int p, int l, int r, int ql, int qr, ll k) {
    if (ql<=l && r<=qr) {
        tree[p].sum += k;
        tree[p].tag1 += k;
        tree[p].msum = max(tree[p].sum, tree[p].msum);
        tree[p].tag2 = max(tree[p].tag2, tree[p].tag1);
        return;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        update(p<<1, l, mid, ql, qr, k);
    }
    if (qr>mid) {
        update(p<<1|1, mid+1, r, ql, qr, k);
    }
    pushUp(p);
}
ll query(int p, int l, int r, int ql, int qr) {
    ll ans = 0;
    if (ql<=l && r<=qr) {
        return tree[p].msum;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        ans = max(ans, query(p<<1, l, mid, ql, qr));
    }
    if (qr>mid) {
        ans = max(ans, query(p<<1|1, mid+1, r, ql, qr));
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i=1;i<=n;++i) {
        scanf("%lld", &a[i]);
        pre[i] = pos[a[i]+100002];
        pos[a[i]+100002] = i;
    }
    scanf("%d", &m);
    for (int i=1;i<=m;++i) {
        scanf("%d %d", &q[i].ql, &q[i].qr);
        q[i].qpos = i;
    }
    sort(q+1, q+m+1, cmp);
    int nowpos = 1;
    for (int i=1,j=1;i<=n;++i) {
        update(1, 1, n, pre[i]+1, i, a[i]);
        while(j<=m&&q[j].qr<=i) {
            ans[q[j].qpos] = query(1, 1, n, q[j].ql, q[j].qr);
            ++j;
        }
    }
    for (int i=1;i<=m;++i) {
        printf("%lld\n", ans[i]);
    }
    return 0;
}