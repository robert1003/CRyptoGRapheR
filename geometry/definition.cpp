struct Pt {
  double x, y;
  Pt(double _x=0, double _y=0):x(_x), y(_y) {}

  Pt operator+(const Pt& a) {
    return Pt(x+a.x, y+a.y);
  }
  Pt operator-(const Pt& a) {
    return Pt(x-a.x, y-a.y);
  }
  Pt operator*(double a) {
    return Pt(x*a, y*a);
  }
  Pt operator/(double a) {
    return Pt(x/a, y/a);
  }
  double operator*(const Pt& a) {
    return x*a.x + y*a.y;
  }
  double operator^(const Pt& a) {
    return x*a.y - y*a.x;
  }
};
double norm2(const Pt& a) {
  return a*a;
}
double norm(const Pt& a) {
  sqrt(norm2(a));
}
Pt perp(const Pt& a) {
  return Pt(-a.y, a.x);
}
Pt rotate(const Pt& a, double ang) {
  return Pt(a.x*cos(ang)-a.y*sin(ang), a.x*sin(ang)+a.y*cos(ang));
}

struct Line {
  Pt s, e, v; // start, end, end-start
  double ang;
  Line(Pt _s=Pt(0, 0), Pt _e=Pt(0, 0)):s(_s), e(_e) { v = e-s; ang = atan2(v.y, v.x); }

  bool operator<(const Line& L) const {
    return ang < L.ang;
  } 
};

struct Circle {
  Pt o; double r;
  Circle(Pt _o=Pt(0, 0), double _r=0):o(_o), r(_r);
};