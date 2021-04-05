#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct node {
    int lc, rc, sum, tag;
    node () {
        lc = rc = sum = tag = 0;
    }
};
node tree[15000007];
int cnt;
int o;
int n, m;

inline void pushUp(int p) {
    tree[p].sum = tree[tree[p].lc].sum + tree[tree[p].rc].sum;
}
inline void pushDown(int p, int l, int r) {
    if (!tree[p].tag) {
        return;
    }
    if (!tree[p].lc) {
        tree[p].lc=++cnt; 
    }
    if (!tree[p].rc) {
        tree[p].rc=++cnt;
    }
    int mid = (l+r)>>1;
    if (tree[p].tag==1) {
        tree[tree[p].lc].sum = mid-l+1;
        tree[tree[p].rc].sum = r-mid; 
    }
    else if (tree[p].tag==2) {
        tree[tree[p].lc].sum = 0;
        tree[tree[p].rc].sum = 0; 
    }
    tree[tree[p].lc].tag = tree[tree[p].rc].tag = tree[p].tag;
    tree[p].tag = 0;
}
void update(int &p, int l, int r, int ql, int qr, int k) {
    if (!p) {
        p=++cnt;
        tree[p].sum = 0;
        tree[p].tag = 2;
    }
    if (ql<=l && r<=qr) {
        tree[p].tag = k;
        if (k==1) {
            tree[p].sum = r-l+1;
        }
        else {
            tree[p].sum = 0; 
        }
        return;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        update(tree[p].lc, l, mid, ql, qr, k);
    }
    if (qr>mid) {
        update(tree[p].rc, mid+1, r, ql, qr, k);
    }
    pushUp(p);
}
int query(int &p, int l,int r, int ql, int qr) {
    if (!p) {
        p=++cnt;
        tree[p].sum = 0;
        tree[p].tag = 2;
    }
    if (ql<=l && r<=qr) {
        return tree[p].sum;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    int ans = 0;
    if (ql<=mid) {
        ans += query(tree[p].lc, l, mid, ql, qr);
    }
    if (qr>mid) {
        ans += query(tree[p].rc, mid+1, r, ql, qr);
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    scanf("%d", &m);
    for (int i=1;i<=m;++i) {
        int opt, x, y;
        scanf("%d %d %d", &x, &y, &opt);
        if (opt==1) {
            update(o, 1, n, x, y, 1);
        }
        else {
            update(o, 1, n, x, y, 2);
        }
        printf("%d\n", n-query(o,1,n,1,n));
    }
    return 0;
}