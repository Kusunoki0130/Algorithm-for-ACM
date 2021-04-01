#include <iostream>
using namespace std;

const int MAXN = 1e2+2;
int dp[MAXN];
int v[MAXN];
int w[MAXN];
int n, V;

int main() {
    cin >> n >> V;
    for (int i=0;i<n;++i) {
        int s;
        cin >> s;
        int minv = 0x7FFFFFFF;
        for (int k=0;k<s;++k) {
            cin >> v[k] >> w[k];
            minv = min(minv, v[k]);
        }
        for (int j=V;j>=minv;--j) {
            for (int k=0;k<s;++k) {
                if (j>=v[k]) {
                    dp[j] = max(dp[j], dp[j-v[k]]+w[k]);
                }
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}