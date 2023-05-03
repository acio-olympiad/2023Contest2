#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 100005
#define LL long long
using namespace std;

class CostQueries {
    // Query given A[l] ... A[r]
    // what is min # additions to make it an nondecreasing sequence
    constexpr static int LG = 20;
    int jmp[MAXN][LG]; // parent
    int N, H[MAXN];
    LL cost[MAXN][LG], psum[MAXN]; // cost of jump, prefix sum on heights

    LL fill_cost(LL l, LL r, LL h) {
        // return cost to fill [l,r] to height h
        return h*(r-l+1) - (psum[r]-psum[l-1]);
    }
public:
    void build(vector<int>& Hin) {
        N = Hin.size();
        vector <int> st; // sorted stack for getting next higher
        for (int i=1; i<=N; i++) {
            H[i] = Hin[i-1];
            psum[i] = psum[i-1] + H[i];
            while (st.size() && H[st.back()] < H[i]) {
                // cost of jump to cur is cost to fill in [back, i-1]
                jmp[st.back()][0] = i;
                cost[st.back()][0] = fill_cost(st.back(), i-1, H[st.back()]);
                st.pop_back();
            }
            st.push_back(i);
            jmp[i][0] = i; // assume it is biggest until popped
        }

        // build jump table & aggregate costs
        for (int i=1; i<LG; i++) {
            for (int j=1; j<=N; j++) {
                jmp[j][i] = jmp[jmp[j][i-1]][i-1];
                cost[j][i] = cost[j][i-1] + cost[jmp[j][i-1]][i-1];
            }
        }
    }

    LL ask(int l, int r) {
        LL ans = 0;
        for (int i = LG-1; i>=0; i--) {
            if (jmp[l][i] <= r) {
                ans += cost[l][i];
                l = jmp[l][i];
            }
        }
        return ans + fill_cost(l,r,H[l]) ;
    }
} costDec, costInc; // cost for decreasing half, cost for increasing half

int N,Q,A[MAXN];
LL Best[MAXN];

void slv(int l, int r, int optlo, int opthi) {
    if (l > r) {return;}
    int mid = (l + r) >> 1;
    Best[mid] = 1LL<<60;
    int optimal = -1;
    for (int i=optlo; i<=min(mid,opthi); i++) {
        LL newCost = costDec.ask(N+1-i,N) + costInc.ask(i,mid);
        if (newCost <= Best[mid]) { // take rightmost optimal point
            // take rightmost optimal point is correct because
            // as r increases the left optimal points increase
            // in cost faster than ones to right
            optimal = i;
            Best[mid] = newCost;
        }
    }
    slv(l, mid-1, optlo, optimal);
    slv(mid+1, r, optimal, opthi);
}

int main() {
    //freopen("nadirin.txt","r",stdin);
    scanf("%d %d",&N,&Q);
    vector <int> A_vec;
    for (int i=1; i<=N; i++) {
        scanf("%d",&A[i]);
        A_vec.push_back(A[i]);
    }

    costInc.build(A_vec);
    reverse(A_vec.begin(), A_vec.end());
    costDec.build(A_vec); // queries for decreasing indexed different

    slv(1, N, 1, N); // calculate solutions

    for (int i=1; i<=Q; i++) {
        int ki;
        scanf("%d",&ki);
        printf("%lld\n",Best[ki]);
    }
}
