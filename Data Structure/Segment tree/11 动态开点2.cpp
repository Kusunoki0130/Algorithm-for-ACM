#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 1e5+5;
struct node {
    int lc, rc, val, tag;
    node () {
        lc = rc = val = tag = 0;
    }
};
node tree[5000007];
int treeb[MAXN<<4];
int b[MAXN];
int n, k, q;
int cnt, o;

void buildTreeb(int p, int l, int r) {
    if (l==r) {
        treeb[p] = b[l];
        return;
    }
    int mid = (l+r)>>1;
    buildTreeb(p<<1, l, mid);
    buildTreeb(p<<1|1, mid+1, r);
    treeb[p] = min(treeb[p<<1], treeb[p<<1|1]);
}
int queryb(int p, int l, int r, int ql, int qr) {
    int ans = 0x7FFFFFFF;
    if (ql<=l && r<=qr) {
        return treeb[p];
    }
    int mid = (l+r)>>1;
    if (ql<=mid) {
        ans = min(ans, queryb(p<<1, l, mid, ql, qr));
    }
    if (qr>mid) {
        ans = min(ans, queryb(p<<1|1, mid+1, r, ql, qr));
    }
    return ans;
}

void newNode(int &p, int l, int r) {
    p = ++cnt;
    //cout << "l=" << l << " " << "r=" << r << " ";
    if (r-l+1>=n) {
        tree[p].val = queryb(1, 1, n, 1, n);
    }
    else {
        l = l%n ? l%n : n;
        r = r%n ? r%n : n;
        //cout << l << " " << r << " ";
        if (l<=r) {
            tree[p].val = queryb(1, 1, n, l, r);
        }
        else {
            tree[p].val = min(queryb(1, 1, n, l, n), queryb(1, 1, n, 1, r));
        }
    }
    //cout << p << " " << tree[p].val << endl;
}
void pushUp(int p) {
    tree[p].val = min(tree[tree[p].lc].val, tree[tree[p].rc].val);
}
void pushDown(int p, int l, int r) {
    int mid = (l+r)>>1;
    if (!tree[p].lc) {
        newNode(tree[p].lc, l, mid);
    }
    if (!tree[p].rc) {
        newNode(tree[p].rc, mid+1, r);
    }
    if (tree[p].tag) {
        tree[tree[p].lc].val = tree[tree[p].rc].val = tree[tree[p].lc].tag = tree[tree[p].rc].tag = tree[p].tag;
        tree[p].tag = 0; 
    }
}
void update(int &p, int l, int r, int ql, int qr, int num) {
    if (!p) {
        newNode(p, l, r);
    }
    if (ql<=l && r<=qr) {
        tree[p].val = tree[p].tag = num;
        return;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        update(tree[p].lc, l, mid, ql, qr, num);
    }
    if (qr>mid) {
        update(tree[p].rc, mid+1, r, ql, qr, num);
    }
    pushUp(p);
}
int query(int &p, int l, int r, int ql, int qr) {
    if (!p) {
        newNode(p, l, r);
    }
    int ans = 0x7FFFFFFF;
    if (ql<=l && r<=qr) {
        return tree[p].val;
    }
    pushDown(p, l, r);
    int mid = (l+r)>>1;
    if (ql<=mid) {
        ans = min(ans, query(tree[p].lc, l, mid, ql, qr));
    }
    if (qr>mid) {
        ans = min(ans, query(tree[p].rc, mid+1, r, ql, qr));
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i=1;i<=n;++i) {
        scanf("%d", &b[i]);
    }
    buildTreeb(1, 1, n);
    scanf("%d", &q);
    for (int i=1;i<=q;++i) {
        int opt, x, y;
        scanf("%d %d %d", &opt, &x, &y);
        if (opt==1) {
            int num;
            scanf("%d", &num);
            update(o, 1, n*k, x, y, num);
        }
        else {
            printf("%d\n", query(o, 1, n*k, x, y));
        }
    }
    return 0;
}