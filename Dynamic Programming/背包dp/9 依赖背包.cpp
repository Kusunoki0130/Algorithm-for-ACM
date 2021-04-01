#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 1e2+2;
int dp[MAXN][MAXN];
int v[MAXN];
int w[MAXN];
int V, n;
vector<int> edge[MAXN];

void dfs(int u) {
    for (int i=0;i<edge[u].size();++i) {
        int uu = edge[u][i];
        dfs(uu);
        for (int j=V-v[u];j>=0;--j) {
            for(int k=0;k<=j;++k) {
                dp[u][j] = max(dp[u][j], dp[u][j-k]+dp[uu][k]);
            }
        }
    }
    for (int i=V;i>=v[u];--i) {
        dp[u][i] = dp[u][i-v[u]]+w[u];
    }
    for (int i=v[u]-1;i>=0;--i) {
        dp[u][i] = 0;
    }
}

int main() {
    cin >> n >> V;
    int rt = -1;
    for (int i=1;i<=n;++i) {
        int f;
        cin >> v[i] >> w[i] >> f;
        if (f!=-1) {
            edge[f].push_back(i);
        }
        else {
            rt = i;
        }
    }
    dfs(rt);
    cout << dp[rt][V] << endl;
    return 0;
}