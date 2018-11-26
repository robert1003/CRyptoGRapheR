bool onseg(Pt p, Line L) { //assume dcmp(x^y)==0
  Pt x = L.s-p, y = L.e-p;
  return dcmp(x*y) <= 0; //inseg:dcmp(x*y)<0
}
Pt SSIntersect(Line a, Line b) {
  Pt p = LLIntersect(a, b);
  if(isinf(p.x)&&(onseg(a.s,b)||onseg(a.e,b)) return p;
  if(isfinite(p.x)&&onseg(p, a)&&onseg(p, b)) return p;
  return {NAN,NAN};
}
