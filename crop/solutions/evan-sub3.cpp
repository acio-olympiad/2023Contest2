#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll

int n,q,k;
int val[100005];
int dp[100005][55][2]; // dp[a][b][c] = Best solution using cells up to a, where cells up to a use the bth (or less) crop. If c=0, the cell a is not included, otherwise the cell a is included.
int ans[55];

signed main(){
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> val[i];
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=50;j++){
            // Calculating dp[i][j]
            dp[i][j][0] = max(dp[i-1][j][0],dp[i-1][j][1]);
            dp[i][j][1] = max(dp[i-1][j][1],dp[i-1][j-1][0])+val[i];
            ans[j] = max(ans[j],dp[i][j][0]);
            ans[j] = max(ans[j],dp[i][j][1]);
        }
    }
    for (int j = 1; j <= 50; j++) {
        ans[j] = max(ans[j], ans[j-1]);
    }
    for (int i = 0; i < q; i++) {
        int a; cin >> a;
        cout << ans[a] << "\n";
    }
    return 0;
}
