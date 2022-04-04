pair<ld,ld> solve(vector<Pt> &hull){ // (Pt>Pt),(f*Pt)
  const ld qi=acos(-1)/2*3; ld Max=0,Min=INF,deg;
  int n=hull.size(); hull.push_back(hull[0]);
  for(int i=0,u=1,r=1,l=0;i<n;++i){
    Pt nw=hull[i+1]-hull[i];
    while((nw^(hull[u+1]-hull[i]))>(nw^(hull[u]-hull[i]))) u=(u+1)%n;
    while((nw*(hull[r+1]-hull[i]))>(nw*(hull[r]-hull[i]))) r=(r+1)%n;
    if(!i) l=(r+1)%n;
    while((nw*(hull[l+1]-hull[i]))<(nw*(hull[l]-hull[i]))) l=(l+1)%n;
    Min=min(Min,(ld)((nw*(hull[r]-hull[i]))-(nw*(hull[l]-hull[i])))*(nw^(hull[u]-hull[i]))/norm2(nw));
    deg=acos((ld)((hull[r]-hull[l])*(hull[u]-hull[i]))/norm(hull[r]-hull[l])/norm(hull[u]-hull[i]));
    deg=(qi-deg)/2;
    Max=max(Max,(ld)norm(hull[r]-hull[l])*norm(hull[u]-hull[i])*sin(deg)*sin(deg));
  }
  return pair<ld,ld>(Min,Max);
} // find min,max enclosing rectangle of a convex hull
