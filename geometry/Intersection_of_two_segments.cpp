bool onseg(Pt p, Line L) {
  Pt x = L.s-p, y = L.e-p;
  return dcmp(x^y) == 0 && dcmp(x*y) <= 0; 
} // inseg: dcmp(x^y)==0&&dcmp(x*y)<0
// assume a.s != a.e != b.s != b.e
Pt SSIntersect(Line a, Line b) {
  Pt p = LLIntersect(a, b);
  if(isinf(p.x)&&(onseg(a.s,b)||onseg(a.e,b)||onseg(b.s,a)||onseg(b.e,a))) return p; // overlap
  if(isfinite(p.x)&&onseg(p,a)&&onseg(p,b)) return p;
  return {NAN,NAN}; // non-intersect
}
