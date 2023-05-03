#include "dumpling.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <cassert>
#include <queue>

using namespace std;

static int N, K, M, S, B;
static int a[100005], b[100005];

// State
static int bowlsize, idlesteps, cnt, delivered, T;
static bool idle;
static vector<int> bowl_dumplings;
static queue<int> evq;

int pop() {
    assert(bowl_dumplings.size() > 0);
    auto it = bowl_dumplings.begin();
    int res = *it;
    bowl_dumplings.erase(it);
    return res;
}

int serve() {
    if (cnt == N) return -1;
    int res = ++cnt;
    if (bowl_dumplings.size() < bowlsize) {
        bowl_dumplings.push_back(res);
    }
    return res;
}

bool should_stop() {
    return bowl_dumplings.size() == 0 && cnt == N;
}

int main() {
    cin >> N >> K >> M >> S >> B;
    for (int i = 1; i <= M; i++) {
        cin >> a[i] >> b[i];
    }
    bowlsize = B;
    for (int i = 0; i < K; i++) evq.push(-1);
    // Call init
    init(S);
    for (T = 1; T <= M && !should_stop(); T++) {
        // Call 
        if (cnt < N) {
            step(evq.front());
            evq.pop();
        }
        // Consume
        if (a[T]) {
            idle = false;
            if (bowl_dumplings.size() > 0) {
                int x = pop();
                delivered++;
                evq.push(x);
            } else {
                idle = true;
                evq.push(-1);
            }
        } else {
            evq.push(-1);
        }

        if (idle) idlesteps++;
        // Update bowl size
        bowlsize += b[T];
        assert(bowlsize > 0);
        if (bowl_dumplings.size() > bowlsize) {
            pop();
        }
    }
    // Output score
    double delivery = (double)delivered / N;
    double efficiency = (double)(T - idlesteps) / T;
    double x = delivery * efficiency;
    double score = min(1.0, max(0.0, max(0.2*x, 4.2*x - 3.2))) * 100.0;

    cout << "total timesteps: " << T << "\n";
    cout << "delivery: " << delivery << "\n";
    cout << "efficiency: " << efficiency << "\n";
    cout << "x: " << x << "\n";
    cout << "score: " << score << "\n";

}
