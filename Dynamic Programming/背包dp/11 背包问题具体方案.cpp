#include <iostream>
using namespace std;

const int MAXN = 1e3+3;
int dp[MAXN];
int pre[MAXN][MAXN];
bool flag[MAXN][MAXN];
int n, V;
int v[MAXN];
int w[MAXN];
bool ans[MAXN];

int main() {
    cin >> n >> V;
    for (int i=1;i<=n;++i) {
        cin >> v[i] >> w[i];
    }
    for (int i=n;i>=1;--i) {
        for (int j=0;j<=V;++j) {
            pre[i][j] = j;
        }
        for (int j=V;j>=v[i];--j) {
            if (dp[j]<=dp[j-v[i]]+w[i]) {
                dp[j] = dp[j-v[i]] + w[i];
                pre[i][j] = j-v[i];
                flag[i][j] = true;
            }
        }
    }
    int x = 1;
    int y = V;
    while(x!=n+1) {
        if (flag[x][y]) {
            ans[x] = true;
        }
        y = pre[x][y];
        ++x;
    }
    for (int i=1;i<=n;++i) {
        if (ans[i]) {
            cout << i << " ";
        }
    }
    return 0;
}
