#include <bits/stdc++.h>
using namespace std;

const long long MAX_VAL = 2e9;
const int MAX = 100002;
long long a[MAX];
long long prefix[MAX];
long long suffix[MAX];
long long pointer[20][MAX];
int N, Q;
long long cost[MAX];
long long optimum[MAX];
vector<long long> queries;
long long sum_prefix[MAX];


void input(){
	cin >> N >> Q;

	a[0] = MAX_VAL;
	a[N + 1] = MAX_VAL;
	for(int i = 1; i <= N; i++){
		cin >> a[i];
	}

	for(int q = 0; q < Q; q++){
		int x;
		cin >> x;
		queries.push_back(x);
	}
}

void make_prefix(){
	stack<int> S;
	prefix[0] = 0;
	S.push(0);

	long long cost = 0;
	sum_prefix[0] = 0;

	for(int i = 1; i <= N; i++){
		sum_prefix[i] = sum_prefix[i - 1] + a[i];

		while(a[S.top()] <= a[i]){
			long long h_min = a[S.top()];
			S.pop();

			long long h = min(a[i], a[S.top()]) - h_min;
			long long interval_size = i - S.top() - 1;
			cost += h * interval_size;
		}

		prefix[i] = cost;
		// cout << "i = " << i << "  prefix cost = " << cost << endl;

		S.push(i);
	}
}

void make_pointer(){
	for(int i = 0; i <= N + 1; i++){
		for(int j = 0; j < 20; j++){
			pointer[j][i] = -1;
		}
	}

	stack<int> S;
	suffix[N + 1] = 0;
	S.push(N + 1);

	long long cost = 0;

	for(int i = N; i >= 1; i--){
		while(a[S.top()] <= a[i]){
			long long h_min = a[S.top()];
			S.pop();

			long long h = min(a[i], a[S.top()]) - h_min;
			long long interval_size = S.top() - i - 1;
			cost += h * interval_size;
		}

		suffix[i] = cost;
		pointer[0][i] = S.top();
		// cout << "i = " << i << "  suffix cost = " << cost << endl;

		S.push(i);
	}

	for(int i = N; i >= 1; i--){
		for(int j = 1; j < 20; j++){
			if(pointer[j - 1][i] != -1){
				pointer[j][i] = pointer[j - 1][pointer[j - 1][i]];
			} else {
				break;
			}
		}
	}
}

long long find_interval_cost(int s, long long e){
	int k = 20;
	long long e2 = s;
	// I want e2 <= e.
	while(k >= 1){
		k--;
		if(pointer[k][e2] == -1) continue;
		if(pointer[k][e2] > e) continue;
		e2 = pointer[k][e2];
	}

	long long result = suffix[s] - suffix[e2];
	result += (e - e2) * a[e2];
	result -= sum_prefix[e] - sum_prefix[e2];

	// cout << "interval: [" << s << ", " << e << "]   cost: " << result << endl;

	return result;
}

void calculate_cost(int a, int b){
	if(b - a <= 1) return;
	int h = (a + b)/2;

	long long opt = -1;
	long long ANS = MAX_VAL*MAX_VAL;

	for(int i = optimum[a]; i <= optimum[b]; i++){
		if(i > h) break;

		long long val = prefix[i] + find_interval_cost(i, h);
		if(val < ANS){
			ANS = val;
			opt = i;
		}
	}

	optimum[h] = opt;
	cost[h] = ANS;
	// cout << "h = " << h << "  " << ANS << endl;

	// afterwards, calculate on two subintervals.
	calculate_cost(a, h);
	calculate_cost(h, b);
}

void process(){
	make_prefix();
	make_pointer();
	
	optimum[0] = 1;
	optimum[N + 1] = N;

	calculate_cost(0, N + 1);
}

void output(){
	for(int i = 0; i < Q; i++){
		cout << cost[queries[i]] << "\n";
	}
}

int main(){
	cin.tie(NULL);
	cout.tie(NULL);
	ios_base::sync_with_stdio(0);

	input();
	process();
	output();
}
