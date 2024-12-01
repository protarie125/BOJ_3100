#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vs = vector<string>;

vs P;

ll Calc(const vl& x, const vl& y, const vl& z) {
  using lc = pair<ll, char>;
  using vlc = vector<lc>;

  vlc X, Y, Z;
  for (auto i = 0; i < 26; ++i) {
    X.push_back({x[i], 'A' + i});
    Y.push_back({y[i], 'A' + i});
    Z.push_back({z[i], 'A' + i});
  }

  sort(X.rbegin(), X.rend());
  sort(Y.rbegin(), Y.rend());
  sort(Z.rbegin(), Z.rend());

  ll ret = 987654321;

  if (Y[0].second != X[0].second) {
    if (Y[0].second != Z[0].second) {
      auto ans = 18 - X[0].first;
      ans += 18 - Y[0].first;
      ans += 18 - Z[0].first;
      ret = min(ret, ans);
    } else {
      // change Y
      if (Y[1].second == X[1].second) {
        auto ans = 18 - X[0].first;
        ans += 18 - Y[2].first;
        ans += 18 - Z[0].first;
        ret = min(ret, ans);
      } else {
        auto ans = 18 - X[0].first;
        ans += 18 - Y[1].first;
        ans += 18 - Z[0].first;
        ret = min(ret, ans);
      }
      // change Z
      if (Z[1].second == X[1].second) {
        auto ans = 18 - X[0].first;
        ans += 18 - Y[0].first;
        ans += 18 - Z[2].first;
        ret = min(ret, ans);
      } else {
        auto ans = 18 - X[0].first;
        ans += 18 - Y[0].first;
        ans += 18 - Z[1].first;
        ret = min(ret, ans);
      }
    }
  } else {  // X == Y
    if (Y[0].second != Z[0].second) {
      // change Y
      if (Y[1].second == Z[1].second) {
        auto ans = 18 - X[0].first;
        ans += 18 - Y[2].first;
        ans += 18 - Z[0].first;
        ret = min(ret, ans);
      } else {
        auto ans = 18 - X[0].first;
        ans += 18 - Y[1].first;
        ans += 18 - Z[0].first;
        ret = min(ret, ans);
      }
      // change X
      if (X[1].second == Z[1].second) {
        auto ans = 18 - X[2].first;
        ans += 18 - Y[0].first;
        ans += 18 - Z[0].first;
        ret = min(ret, ans);
      } else {
        auto ans = 18 - X[1].first;
        ans += 18 - Y[0].first;
        ans += 18 - Z[0].first;
        ret = min(ret, ans);
      }
    } else {  // X == Y == Z
      auto ans = 18 - X[0].first;
      ans += 18 - Y[1].first;
      ans += 18 - Z[0].first;
      ret = min(ret, ans);
    }
  }

  return ret;
}

ll CalcRow() {
  auto r1 = vl(26, 0);
  for (auto i = 0; i < 2; ++i) {
    for (auto j = 0; j < 9; ++j) {
      const auto& x = P[i][j];
      r1[x - 'A'] += 1;
    }
  }

  auto r2 = vl(26, 0);
  for (auto i = 2; i < 4; ++i) {
    for (auto j = 0; j < 9; ++j) {
      const auto& x = P[i][j];
      r2[x - 'A'] += 1;
    }
  }

  auto r3 = vl(26, 0);
  for (auto i = 4; i < 6; ++i) {
    for (auto j = 0; j < 9; ++j) {
      const auto& x = P[i][j];
      r3[x - 'A'] += 1;
    }
  }

  return Calc(r1, r2, r3);
}

ll CalcCol() {
  auto r1 = vl(26, 0);
  for (auto i = 0; i < 6; ++i) {
    for (auto j = 0; j < 3; ++j) {
      const auto& x = P[i][j];
      r1[x - 'A'] += 1;
    }
  }

  auto r2 = vl(26, 0);
  for (auto i = 0; i < 6; ++i) {
    for (auto j = 3; j < 6; ++j) {
      const auto& x = P[i][j];
      r2[x - 'A'] += 1;
    }
  }

  auto r3 = vl(26, 0);
  for (auto i = 0; i < 6; ++i) {
    for (auto j = 6; j < 9; ++j) {
      const auto& x = P[i][j];
      r3[x - 'A'] += 1;
    }
  }

  return Calc(r1, r2, r3);
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  P = vs(6);
  for (auto&& p : P) cin >> p;

  const auto& ans1 = CalcRow();
  const auto& ans2 = CalcCol();

  cout << min(ans1, ans2);

  return 0;
}