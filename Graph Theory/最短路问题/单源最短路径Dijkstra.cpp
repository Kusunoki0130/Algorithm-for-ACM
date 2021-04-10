#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> plli;
const int MAXN = 1e4+4;
const ll INF = 0x7FFFFFFF;
priority_queue<plli, vector<plli>, greater<plli> > q;
vector<plli> edge[MAXN];
ll dis[MAXN];
int n, m, st;

void dijkstra() {
    for (int i=1;i<=n;++i) {
        dis[i] = INF;
    }
    dis[st] = 0;
    q.push(make_pair(dis[st], st));
    while(!q.empty()) {
        int disu = q.top().first;
        int u = q.top().second;
        q.pop();
        if (disu>dis[u]) {
            continue;
        }
        for (int i=0;i<edge[u].size();++i) {
            int v = edge[u][i].second;
            int w = edge[u][i].first;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &st);
    for (int i=0;i<m;++i) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        if (u==v) {
            continue;
        }
        edge[u].push_back(make_pair(w, v));
    }
    dijkstra();
    for (int i=1;i<=n;++i) {
        printf("%lld ", dis[i]);
    }
    return 0;
}