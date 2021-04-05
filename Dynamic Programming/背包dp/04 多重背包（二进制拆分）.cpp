#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2e3+3;
long long dp[MAXN];
int n, V;

int main() {
    cin >> n >> V;
    for (int i=0;i<n;++i) {
        int v, w, s;
        cin >> v >> w >> s;
        int base = 1;
        while(s>0) {
            int tmpv = (s>base?base:s)*v;
            int tmpw = (s>base?base:s)*w;
            s -= base;      
            for (int j=V;j>=tmpv;--j) {
                dp[j] = max(dp[j], dp[j-tmpv]+tmpw);
            }
            base *= 2;
        }
    }
    cout << dp[V] << endl;
    return 0;
}