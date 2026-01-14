#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define ll long long
#define ld long double
#define mp make_pair
#define nl "\n"

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0);

int main() {
    FAST_IO;
    int n,m,q;
    cin>>n>>m;
    vector<vector<ll>>dp(n+1,vector<ll>(n+1,1e18));
    for(int i=0;i<=n;i++){
        dp[i][i]=0;
    }
    for(int i=0;i<m;i++){
        int a,b;
        ll c;
        cin>>a>>b>>c;
        if(c<dp[a][b]){
            dp[a][b]=c;
        }
    }
    int y,z;
    cin>>y>>z;
    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dp[i][k]<1e18 && dp[k][j]<1e18 && dp[i][j]>dp[i][k]+dp[k][j]){
                    dp[i][j]=dp[i][k]+dp[k][j];
                }
            }
        }
    }
    cin>>q;
    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        if(min(dp[a][y]+dp[y][b],dp[a][z]+dp[z][b])>=1e18){
            cout<<-1<<nl;
        }
        else{
            cout<<min(dp[a][y]+dp[y][b],dp[a][z]+dp[z][b])<<nl;
        }
    }
    return 0;
}