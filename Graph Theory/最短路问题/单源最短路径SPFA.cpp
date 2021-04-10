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
queue<int> q;
vector<plli> edge[MAXN];
ll dis[MAXN];
bool vis[MAXN];
int n, m, st;

void spfa() {
    for (int i=1;i<=n;++i) {
        vis[i] = false;
        dis[i] = INF;
    }
    dis[st] = 0;
    vis[st] = true;
    q.push(st);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for (int i=0;i<edge[u].size();++i) {
            int v = edge[u][i].second;
            int w = edge[u][i].first;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
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
    spfa();
    for (int i=1;i<=n;++i) {
        printf("%lld ", dis[i]);
    }
    return 0;
}