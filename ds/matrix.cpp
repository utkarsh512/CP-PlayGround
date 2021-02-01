template <class T>
struct Mat {
  vector<vector<T>> a;
  int n, m;

  Mat() {}

  Mat(int _n, int _m) : n(_n), m(_m) {
    a = vector<vector<T>>(n, vector<T>(m));
  }

  Mat(int _n, int _m, T val) : n(_n), m(_m) {
    a = vector<vector<T>>(n, vector<T>(m, val));
  }

  Mat(const vector<T>& oth) {
    a = vector<vector<T>>(sz(oth), vector<T>(1));
    n = sz(oth);
    m = 1;
    for (int i = 0; i < sz(oth); i++) {
      a[i][0] = oth[i];
    }
  }

  Mat(const vector<vector<T>>& oth) {
    a = oth;
    n = sz(a);
    m = sz(a[0]);
  }

  Mat operator*(const Mat& oth) const {
    assert(m == oth.n);
    Mat r(n, oth.m);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < oth.m; j++) {
        for (int k = 0; k < m; k++) {
          r.a[i][j] += a[i][k] * oth.a[k][j];
        }
      }
    }
    return r;
  }

  Mat& operator*=(const Mat& oth) {
    *this = (*this) * oth;
    return *this;
  }

  template<class U> friend Mat power(const Mat& a, const U& b) {
    assert(b >= 0);
    assert(a.n == a.m);
    Mat x = a;
    Mat res(a.n, a.m);
    for (int i = 0; i < a.n; i++) res.a[i][i] = 1;
    U p = b;
    while (p > 0) {
      if (p & 1) res *= x;
      x *= x;
      p >>= 1;
    }
    return res;
  }
};
