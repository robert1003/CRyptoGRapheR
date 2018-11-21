bool onseg(Pt p, Line L) {
  Pt x = L.s-p, y = L.e-p;
  return dcmp(x^y) == 0 && dcmp(x*y) <= 0; // inseg: dcmp(x*y) < 0
}
Pt SSIntersect(Line a, Line b) {
  Pt p1 = a.s, p2 = a.e, q1 = b.s, q2 = b.e;
  Pt p = LLIntersect(a, b);
  if(!isnan(p.x) && onseg(p, a) && onseg(p, b)) return q;
  return Pt(nan(""), nan(""));
}