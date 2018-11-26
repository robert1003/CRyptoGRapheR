Pt LLIntersect(Line a, Line b) {
  Pt p1 = a.s, p2 = a.e, q1 = b.s, q2 = b.e;
  double f1 = (p2-p1)^(q1-p1), f2 = (p2-p1)^(p1-q2);
  double f = f1+f2;
  if(dcmp(f) == 0) return {nan(""), nan("")};
  return q1*(f2/f) + q2*(f1/f);
}
