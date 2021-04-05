// https://www.luogu.com.cn/problem/P1637 

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <utility>
using namespace std;

typedef long long ll;
typedef pair<ll, int> plli;
const int MAXN = 3e4+4;
ll tree[MAXN<<4];
plli a[MAXN];
plli num[MAXN];
int sum[MAXN];
int flag[MAXN];
ll ans;
int n;

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
        scanf("%lld", &a[i].first);
        a[i].second = i;
    }
    sort(a+1, a+n+1);
    ll pre = -1;
    int rank = 0;
    for (int i=1;i<=n;++i) {
        if (pre!=a[i].first) {
            pre = a[i].first;
            ++rank;
        }
        num[a[i].second].first = rank;
        num[a[i].second].second = i;       
    }
    int cnt = 0;
    pre = -1;
    for (int i=n;i>=1;--i) {
        if (pre!=a[i].first) {
            pre = a[i].first;
            sum[i] = sum[i+1] + cnt;
            cnt = 1;
        }
        else {
            ++cnt;
            sum[i] = sum[i+1];
        }
    }
    for (int i=1;i<=n;++i) {
        ++flag[num[i].first];
        update(1, 1, rank, num[i].first);
        ll temp1 = query(1, 1, rank, 1, num[i].first)-flag[num[i].first];
        ll temp2 = sum[num[i].second]-(i-temp1-flag[num[i].first]);
        ans += temp1*temp2;
    }
    printf("%lld\n", ans);
    return 0;
}
