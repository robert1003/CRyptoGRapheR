vector<Line> PCTangent(const Circle& C,const Pt& P){
  vector<Line> ans; Pt u=C.o-P; double dist=norm(u);
  if(dist<C.r) return ans;
  else if(abs(dist)<eps){
    ans.push_back({P,P+rotate(u,M_PI/2)});
    return ans;
  }
  else{
    double ang=asin(C.r/dist);
    ans.push_back({P,P+rotate(u,-ang)});
    ans.push_back({P,P+rotate(u,+ang)});
    return ans;
  }
}
