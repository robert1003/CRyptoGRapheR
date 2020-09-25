vector<Pt> interCircle( Pt o1 , ld r1 , Pt o2 , ld r2 ){
  if( norm( o1 - o2 ) > r1 + r2 ) return {};
  if( norm( o1 - o2 ) < max(r1, r2) - min(r1, r2) ) return {};
  ld d2 = ( o1 - o2 ) * ( o1 - o2 );
  ld d = sqrt(d2);
  if( d > r1 + r2 ) return {};
  Pt u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
  ld A = sqrt((r1+r2+d)*(r1-r2+d)*(r1+r2-d)*(-r1+r2+d));
  Pt v = Pt( o1.Y-o2.Y , -o1.X + o2.X ) * A / (2*d2);
  return {u+v, u-v};
}
