#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

const int MAXN = 1e3+3;
int dp[MAXN];
int n, V;

int main() {
    cin >> n >> V;
    for (int i=0;i<n;++i) {
        int v, w, s;
        cin >> v >> w >> s;
        if (s==-1) {
            for (int j=V;j>=v;--j) {
                dp[j] = max(dp[j], dp[j-v]+w);
            }
        }
        else if (s==0) {
            for (int j=v;j<=V;++j) {
                dp[j] = max(dp[j], dp[j-v]+w);
            }
        }
        else {
            int base = 1;
            while(s>0) {
                int tmpv = (s>base?base:s)*v;
                int tmpw = (s>base?base:s)*w;
                s -= base;
                base *= 2;
                for (int j=V;j>=tmpv;--j) {
                    dp[j] = max(dp[j], dp[j-tmpv]+tmpw);
                }
            }
        }
    }
    cout << dp[V] << endl;
    return 0;
}