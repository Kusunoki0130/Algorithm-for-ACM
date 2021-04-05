#include <iostream>
#include <queue>
using namespace std;

const int MAXN = 2e4+4;
int dp[2][MAXN];
int n,V;
int q[MAXN];

int main() {
    cin >> n >> V;
    for (int i=1;i<=n;++i) {
        int v, w, s;
        cin >> v >> w >> s;
        int now = i%2;
        int pre = 1-now;
        for (int j=0;j<v;++j) {
            int st = 0;
            int ed = -1;
            for (int k=j;k<=V;k+=v) {
                if (st<=ed && k-s*v>q[st]) {
                    ++st;
                }
                while(st<=ed && dp[pre][q[ed]]-q[ed]/v*w<=dp[pre][k]-k/v*w) {
                    --ed;
                }
                if (st<=ed) {
                    dp[now][k] = max(dp[pre][k], dp[pre][q[st]]+(k-q[st])/v*w);
                }
                else {
                    dp[now][k] = dp[pre][k];
                }
                q[++ed] = k;
            }
        }
    }
    // cout << dp[(n-1)&1][V] << endl;
    cout << dp[n%2][V] << endl;
    return 0;
}