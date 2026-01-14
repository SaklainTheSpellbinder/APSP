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
    int n;
    cin>>n;
    vector<vector<double>>dp(n+1,vector<double>(n+1,1e15));
    for(int i=0;i<=n;i++){
        dp[i][i]=0.0;
    }
    unordered_map<string,int>mp;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        mp[s]=i;
    }
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        string a,b;
        double c;
        cin>>a>>c>>b;
        double weight=-log(c);
        if(weight<dp[mp[a]][mp[b]]){
            dp[mp[a]][mp[b]]=weight;
        }
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dp[i][k]<1e15 && dp[k][j]<1e15 && dp[i][j]>dp[i][k]+dp[k][j]){
                    dp[i][j]=dp[i][k]+dp[k][j];
                }
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(dp[i][i]<-1e-9){
            cout<<"Yes"<<nl;
            return 0;
        }
    }
    cout<<"No"<<nl;
    return 0;
}