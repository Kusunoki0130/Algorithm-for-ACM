#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
const int MAXN = 2e3+3;
const int INF = 0x3f3f3f3f;
priority_queue<pii, vector<pii>, greater<pii> > q;
vector<pii> edge[MAXN];
int dis[MAXN];
int cnt[MAXN];
int n, m, st;

void dijkstra() {
    for (int i=1;i<=n;++i) {
        dis[i] = INF;
        cnt[i] = 0;
    }
    cnt[1] = 1;
    dis[1] = 0;
    q.push(make_pair(0, 1));
    while(!q.empty()) {
        int u = q.top().second;
        int disu = q.top().first;
        q.pop();
        if (disu>dis[u]) {
            continue;
        }
        for (int i=0;i<edge[u].size();++i) {
            int v = edge[u][i].second;
            int w = edge[u][i].first;
            if (dis[v] == dis[u] + w) {
                cnt[v] += cnt[u];
            }
            else if (dis[v] > dis[u] + w) {
                cnt[v] = cnt[u];
                dis[v] = dis[u] + w;
                q.push(make_pair(dis[v], v));
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i=0;i<m;++i) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edge[u].push_back(make_pair(w, v));
    }
    dijkstra();
    if (dis[n]==INF) {
        printf("No answer\n");
    }
    else {
        printf("%d %d\n", dis[n], cnt[n]);
    }
    return 0;
}