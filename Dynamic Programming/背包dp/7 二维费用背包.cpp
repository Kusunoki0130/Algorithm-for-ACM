#include <iostream>
using namespace std;

const int MAXN = 1e2+2;
int dp[MAXN][MAXN];
int n, V, M;

int main() {
    cin >> n >> V >> M;
    for (int i=1;i<=n;++i) {
        int v, m, w;
        cin >> v >> m >> w;
        for (int j=V;j>=v;--j) {
            for (int k=M;k>=m;--k) {
                dp[j][k] = max(dp[j][k], dp[j-v][k-m]+w);
            }
        }
    }
    cout << dp[V][M] << endl;
    return 0;
}