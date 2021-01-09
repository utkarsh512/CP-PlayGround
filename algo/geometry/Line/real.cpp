/**
 * Description: Handling Lines in 2D geometry (for real case)
 * Caution: 
 * * include Point as well
 */

double det(double a, double b, double c, double d) {
  return a * d - b * c;
}

struct Line {
  double a, b, c;
  Line() {}
  Line(double a_, double b_, double c_) : a(a_), b(b_), c(c_) {}
  Line(const Point<double>& P, const Point<double>& Q) {
    a = P.y - Q.y;
    b = Q.x - P.x;
    c = -1.0 * (a * P.x + b * P.y);

    double z = (double) sqrt(a * a + b * b);
    if (z > eps) {
      a /= z; b /= z; c /= z;
    }
    if (a < (-eps) || (abs(a) < eps && b < (-eps))) {
      a *= -1; b *= -1; c *= -1;
    }
  }

  bool operator==(const Line& oth) {
    double A = abs(det(a, b, oth.a, oth.b));
    double B = abs(det(a, c, oth.a, oth.c));
    double C = abs(det(b, c, oth.b, oth.c));
    return (A < eps && B < eps && C < eps);
  }

  bool isect(const Line& oth) {
    double z = det(a, b, oth.a, oth.b);
    if (abs(z) < eps) return false;
    return true;
  }

  Point isect_point(const Line& oth) {
    double z = det(a, b, oth.a, oth.b);
    double x = -det(c, b, oth.c, oth.b) / z;
    double y = -det(a, c, oth.a, oth.c) / z;
    return Point(x, y);
  }

  friend string to_string(const Line& L) {
    return to_string(make_tuple(L.a, L.b, L.c));
  }
};
