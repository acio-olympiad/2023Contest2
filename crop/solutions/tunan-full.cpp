#include <iostream>
#include <queue>
#include <utility>
#include <map>
#include <cassert>

using namespace std;

typedef pair<int, int> pii;

int N, M, Q;
int a[100005], b[100005];
int ans[100005];
priority_queue<pii, vector<pii>, greater<pii>> s;
map<int, int> m;

void print_state() {
#ifdef DEBUG
    cout << "State:\n";
    for (auto [a, b] : m) {
        cout << "(" << a << ", " << b << ")\n";
    }
#endif
}

void debug_print_all_answers() {
#ifdef DEBUG
    for (int i = 1; i <= N; i++) {
        cout << "ans[" << i << "]: " << ans[i] << "\n";
    }
#endif
}

bool cleanup() {
    if (m.size() > 0 && m.begin()->second <= 0) {
        m.erase(m.begin());
        return false;
    }
    if (m.size() > 0 && m.rbegin()->second <= 0) {
        m.erase(--m.end());
        return false;
    }
    return true;
}

int main() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    int cur = 0;
    /*
    for (int i = 0; i < N && a[i] <= 0; i++) {
        a[i] = 0;
    }
    for (int i = N-1; i >= 0 && a[i] <= 0; i--) {
        a[i] = 0;
    }
    */
    for (int i = 0; i < N; i++) {
        if ((a[i] < 0 && b[cur] > 0) || (a[i] > 0 && b[cur] < 0)) {
            cur++;
        }
        b[cur] += a[i];
    }
    M = cur + 1;
    int pos = 0;
    for (int i = 0; i < M; i++) {
        m[i] = b[i];
        if (b[i] > 0) {
            ans[N] += b[i];
            pos++;
        }
    }
    for (int i = pos; i < N; i++) {
        ans[i] = ans[N];
    }
    for (int i = 0; i < M; i++) {
        s.emplace(abs(b[i]), i);
    }
    print_state();
    int total = M;
    while (s.size() > 1 && pos > 0) {
        // Cleanup both sides
        if (!cleanup()) continue;
        // Iterate
        assert(pos > 0);
        auto e = s.top(); s.pop();
        auto [_, i] = e;
        ans[pos-1] = ans[pos];
        auto it2 = m.find(i);
        if (it2 == m.end()) continue;
        print_state();
        int total = it2->second;
        ans[pos-1] -= max(0, it2->second);
        if (m.find(i) != m.begin()) {
            auto it1 = prev(m.find(i));
            total += it1->second;
            ans[pos-1] -= max(0, it1->second);
            m.erase(it1);
        }
        if (++m.find(i) != m.end()) {
            auto it3 = next(m.find(i));
            total += it3->second;
            ans[pos-1] -= max(0, it3->second);
            m.erase(it3);
        }
        m.erase(m.find(i));
        s.emplace(abs(total), i);
        m[i] = total;
        print_state();
        ans[pos-1] += max(0, total);
        pos--;
    }
    assert(pos <= 1);
    debug_print_all_answers();
    for (int i = 0; i < Q; i++) {
        int q;
        cin >> q;
        cout << ans[q] << "\n";
    }
}
