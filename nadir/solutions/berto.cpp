#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

constexpr int lg = 18;

i64 cld(i64 a, i64 b) {
  // assumes a, b > 0 ig
  return (a + b - 1) / b;
}

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto &x : a) cin >> x;
  a.push_back(1e9 + 5);

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

  for (int k = 1; k < lg; ++k) {
    for (int i = 0; i <= n; ++i) {
      next_r[i][k] = next_r[next_r[i][k - 1]][k - 1];
      sum_r[i][k] = sum_r[i][k - 1] + sum_r[next_r[i][k - 1]][k - 1];
    }
  }

  // (index, first time)
  vector<pair<int, int>> opts;
  for (int jj = 0; jj < n; ++jj) {
    int mn_t = 0;

    while (!opts.empty()) {
      auto [i, mn_t_i] = opts.back();
      int j = jj;

      i64 csm_i = sum_l[i];
      i64 csm_j = sum_l[j];

      csm_i -= a[i];
      for (int k = lg; k--;) {
        if (next_r[i][k] <= j) {
          csm_i += sum_r[i][k];
          i = next_r[i][k];
        }
      }
      csm_i += i64(j - i + 1) * a[i];

      if (csm_j <= csm_i) {
        mn_t = j;
        goto mn_t_get;
      }

      csm_i -= a[i];
      csm_j -= a[j];
      for (int k = lg; k--;) {
        if (next_r[j][k] < n && a[next_r[j][k]] <= a[i] &&
            csm_i + i64(next_r[j][k] - j) * a[i] < csm_j + sum_r[j][k]) {
          csm_j += sum_r[j][k];
          csm_i += i64(next_r[j][k] - j) * a[i];
          j = next_r[j][k];
        }
      }

      if (csm_j <= csm_i || a[i] == a[j]) {
        mn_t = n;
        goto mn_t_get;
      }

      mn_t = min<i64>(n, j + cld(csm_j - csm_i, a[i] - a[j]) - 1);
      if (mn_t >= next_r[j][0]) mn_t = n;

    mn_t_get:
      if (mn_t > mn_t_i) break;
      opts.pop_back();
    }

    opts.push_back({jj, mn_t});
  }

  vector<i64> true_sum_l(n);
  for (int i = 0; i < n; ++i) {
    true_sum_l[i] = (i > 0 ? true_sum_l[i - 1] : 0) + a[i];
  }

  vector<i64> ans(n);
  int cur_t = 0, cur_mx = 0;
  for (auto [i, mn_t] : opts) {
    while (cur_t < mn_t) {
      cur_mx = max(cur_mx, a[cur_t]);
      ans[cur_t] = ans[cur_t - 1] + cur_mx - a[cur_t];
      cur_t++;
    }

    if (mn_t >= n) break;

    i64 csm = sum_l[i] - a[i];
    for (int k = lg; k--;) {
      if (next_r[i][k] <= mn_t) {
        csm += sum_r[i][k];
        i = next_r[i][k];
      }
    }
    csm += i64(mn_t - i + 1) * a[i];

    ans[mn_t] = csm - true_sum_l[mn_t];
    cur_t = mn_t + 1;
    cur_mx = a[i];
  }

  while (q--) {
    int k;
    cin >> k, k--;
    cout << ans[k] << '\n';
  }
}