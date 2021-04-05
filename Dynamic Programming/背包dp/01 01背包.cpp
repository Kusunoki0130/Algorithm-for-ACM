#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1e3+3;
int dp[MAXN];
int n, V;

int main() {
    cin >> n >> V;
    for (int i=0;i<n;++i) {
        int v, w;
        cin >> v >> w;
        for (int j=V;j>=v;--j) {
            dp[j] = max(dp[j], dp[j-v]+w);
        }
    }
    cout << dp[V] << endl;
    return 0;
}