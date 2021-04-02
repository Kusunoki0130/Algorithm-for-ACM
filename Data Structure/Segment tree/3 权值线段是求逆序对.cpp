#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
const int MAXN = 5e5+5;
int tree[MAXN<<4];
pii a[MAXN];
int num[MAXN];
int n;
ll ans;

inline void pushUp(int p) {
    tree[p] = tree[p<<1] + tree[p<<1|1];
}
void update(int p, int l, int r, int pos) {
    if (l==r) {
        ++tree[p];
        return;
    }
    int mid = (l+r)>>1;
    if (pos<=mid) {
        update(p<<1, l, mid, pos);
    }
    else {
        update(p<<1|1, mid+1, r, pos);
    }
    pushUp(p);
    return;
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
    scanf("%d", &n);
    for (int i=1;i<=n;++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a+1, a+n+1);
    int pre = -1;
    int rank = 0;
    for (int i=1;i<=n;++i) {
        if (a[i].first!=pre) {
            pre = a[i].first;
            ++rank;
        }
        num[a[i].second] = rank;
    }
    for (int i=1;i<=n;++i) {
        update(1, 1, rank, num[i]);
        ans += query(1, 1, rank, num[i]+1, rank);
    }
    printf("%lld\n", ans);
    return 0;
}