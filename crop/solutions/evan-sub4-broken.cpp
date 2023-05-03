#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll

int n,q,k,ans;
int val[100005];
int newn,newval[100005];
int lef[100005],rit[100005];
set<vector<int>> s;

signed main(){
	ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> val[i];
    }
    cin >> k;
    int curr=-1;
    for(int i=1;i<=n;i++){
        if((curr<0 and val[i]<=0) or (curr>0 and val[i]>=0)){
            curr += val[i];
        }
        else{
            newval[newn] = curr;
            newn++;
            curr = val[i];
        }
    }
    newval[newn] = curr;
    for(int i=1;i<=newn;i++){
        if(i!=1){
            lef[i] = i-1;
        }
        else{
            lef[i] = 1e9;
        }
        if(i!=newn){
            rit[i] = i+1;
        }
        else{
            rit[i] = 1e9;
        }
        s.insert({abs(newval[i]),i});
        if(newval[i]>0){
            ans += newval[i];
        }
    }
    int npos = (newn+1)/2;
    while(npos>k){
        auto it = s.begin();
        ans -= (*it)[0];
        int x = (*it)[1];
        if(lef[x]==1e9){
            s.erase({abs(newval[x]),x});
            s.erase({abs(newval[rit[x]]),rit[x]});
            lef[rit[rit[x]]] = 1e9;
        }
        else if(rit[x]==1e9){
            s.erase({abs(newval[x]),x});
            s.erase({abs(newval[lef[x]]),lef[x]});
            rit[lef[lef[x]]] = 1e9;
        }
        else{
            s.erase({abs(newval[x]),x});
            s.erase({abs(newval[lef[x]]),lef[x]});
            s.erase({abs(newval[rit[x]]),rit[x]});
            newval[x] += newval[lef[x]]+newval[rit[x]];
            s.insert({abs(newval[x]),x});
            if(lef[lef[x]]!=1e9){
                rit[lef[lef[x]]] = x;
            }
            if(rit[rit[x]]!=1e9){
                lef[rit[rit[x]]] = x;
            }
            lef[x] = lef[lef[x]];
            rit[x] = rit[rit[x]];
        }
        npos--;
    }
    cout << ans << "\n";
    return 0;
}
