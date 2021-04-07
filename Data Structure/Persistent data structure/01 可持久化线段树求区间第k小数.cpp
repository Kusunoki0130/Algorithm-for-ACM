#include <iostream>
#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

typedef pair<int, int> pii;
const int MAXN = 2e5+5;
struct node {
    int lc, rc, sum;
    node () {
        lc = rc = sum = 0;
    }
};
node tree[MAXN<<6];
pii a[MAXN];
int rankCheck[MAXN];
int num[MAXN];
int n, m;
int o[MAXN];
int cnt;

inline int lsh() {
    int rank = 0;
    int pre = -1000000009;
    sort(a+1, a+n+1);
    for (int i=1;i<=n;++i) {
        if (a[i].first!=pre) {
            pre = a[i].first;
            ++rank;
            rankCheck[rank] = a[i].first;
        }
        num[a[i].second] = rank;
    }
    return rank;
}

void buildTree(int &p, int l, int r) {
    if (!p) {
        p = ++cnt;
    }
    if (l==r) {
        return;
    }
    int mid = (l+r)>>1;
    buildTree(tree[p].lc, l, mid);
    buildTree(tree[p].rc, mid+1, r);
}
void update(int &p, int pre, int l, int r, int pos) {
    if (!p) {
        p = ++cnt;
        tree[p].sum = tree[pre].sum;
    }
    if (l==r && l==pos) {
        ++tree[p].sum;
        return;
    }
    int mid = (l+r)>>1;
    if (l<=pos && pos<=mid) {
        tree[p].rc = tree[pre].rc;
        update(tree[p].lc, tree[pre].lc, l, mid, pos);
    }
    else if (mid<pos && pos<=r) {
        tree[p].lc = tree[pre].lc;
        update(tree[p].rc, tree[pre].rc, mid+1, r, pos);
    }
    tree[p].sum = tree[tree[p].lc].sum + tree[tree[p].rc].sum;
}
int query(int lnode, int rnode, int l, int r, int k) {
    int ans = -1;
    if (l==r) {
        return l;
    }
    int mid = (l+r)>>1;
    int lcnt = tree[tree[rnode].lc].sum-tree[tree[lnode].lc].sum;
    if (k<=lcnt) {
        ans = query(tree[lnode].lc, tree[rnode].lc, l, mid, k);
    }
    else {
        ans = query(tree[lnode].rc, tree[rnode].rc, mid+1, r, k-lcnt);
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i=1;i<=n;++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    int len = lsh();
    buildTree(o[0], 1, len);
    for (int i=1;i<=n;++i) {
        update(o[i], o[i-1], 1, len, num[i]);
    }
    for (int i=1;i<=m;++i) {
        int ql, qr, k;
        scanf("%d %d %d", &ql, &qr, &k);
        printf("%d\n", rankCheck[query(o[ql-1], o[qr], 1, len, k)]);
    }
    return 0;
}