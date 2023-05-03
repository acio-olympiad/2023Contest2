#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

const i64 inf = 1e18;
constexpr int lg = 18;

template <class F> struct fix {
  F f;

  template <class... Args> decltype(auto) operator()(Args &&...args) {
    return f(*this, forward<Args>(args)...);
  }
};

template <class F> fix(F) -> fix<F>;

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto &x : a) cin >> x;

  vector<i64> sum_l(n);

  vector<int> pts;
  int curr_edge = -1;
  auto last_sum = [&]() {
    int p = pts.size() > 1 ? pts.end()[-2] : curr_edge;
    return i64(pts.back() - p) * a[pts.back()];
  };

  i64 csm = 0;
  for (int i = 0; i < n; ++i) {
    while (!pts.empty() && a[pts.back()] <= a[i]) {
      csm -= last_sum();
      pts.pop_back();
    }

    pts.push_back(i);
    csm += last_sum();
    sum_l[i] = csm;
  }

  vector<array<int, lg>> next_r(n + 1);
  vector<array<i64, lg>> sum_r(n + 1);

  pts.clear();
  curr_edge = n;
  for (int i = n; i--;) {
    while (!pts.empty() && a[pts.back()] <= a[i]) {
      pts.pop_back();
    }

    next_r[i][0] = !pts.empty() ? pts.back() : n;
    pts.push_back(i);
    sum_r[i][0] = -last_sum();
  }
  next_r[n][0] = n;
  sum_r[n][0] = 0;

  for (int k = 0; k + 1 < lg; ++k) {
    for (int i = 0; i <= n; ++i) {
      int j = next_r[i][k];
      next_r[i][k + 1] = next_r[j][k];
      sum_r[i][k + 1] = sum_r[i][k] + sum_r[j][k];
    }
  }

  auto f = [&](int r, int i) -> i64 {
    if (r < i) return inf;

    i64 res = sum_l[i] - a[i];
    for (int k = lg; k--;) {
      if (next_r[i][k] <= r) {
        res += sum_r[i][k];
        i = next_r[i][k];
      }
    }
    res += i64(r - i + 1) * a[i];
    return res;
  };

  vector<pair<i64, int>> ans(n);

  auto solve = fix{[&](auto solve, vector<int> &rs, vector<int> &cs) -> void {
    if (rs.empty()) return;

    auto cmp = [&](int r, int c1, int c2) { return f(r, c1) > f(r, c2); };

    const int r = rs.size();
    vector<int> ccs, rev;
    ccs.reserve(r), rev.reserve(r);
    for (int i = 0; i < cs.size(); ++i) {
      const int c = cs[i];
      while (!ccs.empty() && cmp(rs[ccs.size() - 1], ccs.back(), c)) {
        ccs.pop_back();
        rev.pop_back();
      }
      if (ccs.size() < r) {
        ccs.push_back(c);
        rev.push_back(i);
      }
    }

    {
      vector<int> rrs;
      rrs.reserve(r / 2);
      for (int i = 1; i < r; i += 2) rrs.push_back(rs[i]);
      solve(rrs, ccs);
    }

    for (int i = 0; i < r; i += 2) {
      int opt_l = i > 0 ? ans[rs[i - 1]].second : 0,
          opt_r = i + 1 < r ? ans[rs[i + 1]].second : ccs.size() - 1;

      pair opt = {inf, -1};
      for (int j = opt_l; j <= opt_r; ++j) {
        opt = min(opt, {f(rs[i], ccs[j]), j});
      }
      ans[rs[i]] = opt;
    }

    for (int r : rs) ans[r].second = rev[ans[r].second];
  }};

  {
    vector<int> rs(n), cs(n);
    iota(begin(rs), end(rs), 0);
    iota(begin(cs), end(cs), 0);
    solve(rs, cs);
  }

  vector<i64> true_sum_l(n);
  for (int i = 0; i < n; ++i) {
    true_sum_l[i] = (i > 0 ? true_sum_l[i - 1] : 0) + a[i];
    ans[i].first -= true_sum_l[i];
  }

  while (q--) {
    int k;
    cin >> k, k--;
    cout << ans[k].first << '\n';
  }
}