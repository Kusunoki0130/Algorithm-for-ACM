#include <iostream>
using namespace std;

const int MOD = 1e9+7;
const int MAXN = 1e3+3;
int dp[MAXN];
int cnt[MAXN];
int n, V;

int main() {
    cin >> n >> V;
    for (int i=0;i<=V;++i) {
        cnt[i] = 1;
    }
    for (int i=0;i<n;++i) {
        int v, w;
        cin >> v >> w;
        for (int j=V;j>=v;--j) {
            if (dp[j]<dp[j-v]+w) {
                dp[j] = dp[j-v] + w;
                cnt[j] = cnt[j-v];
            }
            else if (dp[j]==dp[j-v]+w) {
                cnt[j] = (cnt[j] + cnt[j-v])%MOD;
            }
        }
    }
    cout << cnt[V] << endl;
    return 0;
}