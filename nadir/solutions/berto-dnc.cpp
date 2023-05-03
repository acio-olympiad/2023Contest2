#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

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

  vector<i64> ans(n);

  auto get_opt = [&](int m, int l, int r) {
    l = min(l, m);
    r = min(r, m);

    i64 cur_r = 0;
    {
      int rr = r;
      for (int k = lg; k--;) {
        if (next_r[rr][k] <= m) {
          cur_r += sum_r[rr][k];
          rr = next_r[rr][k];
        }
      }
      cur_r += i64(m - rr + 1) * a[rr];
    }

    int opt = r;
    i64 opt_val = sum_l[r] + cur_r - a[r];

    for (int i = r; i-- > l;) {
      if (next_r[i][0] > m) {
        cur_r = i64(m - i + 1) * a[i];
      } else {
        cur_r += sum_r[i].back() - sum_r[i + 1].back();
      }

      if (i64 cur_val = sum_l[i] + cur_r - a[i]; cur_val <= opt_val) {
        opt = i;
        opt_val = cur_val;
      }
    }

    return pair{opt, opt_val};
  };

  auto solve = fix{[&](auto &solve, int st, int en, int l, int r) {
    if (st > en) return;

    int m = (st + en) / 2;
    auto [opt, opt_val] = get_opt(m, l, r);

    ans[m] = opt_val;

    solve(st, m - 1, l, opt);
    solve(m + 1, en, opt, r);
  }};

  solve(0, n - 1, 0, n - 1);

  vector<i64> true_sum_l(n);
  for (int i = 0; i < n; ++i) {
    true_sum_l[i] = (i > 0 ? true_sum_l[i - 1] : 0) + a[i];
    ans[i] -= true_sum_l[i];
  }

  while (q--) {
    int k;
    cin >> k, k--;
    cout << ans[k] << '\n';
  }
}