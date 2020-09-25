double TwoConvexHullMinDis(Point P[], Point Q[], int n, int m) {
  int YMinP=0, YMaxQ=0; double tmp, ans=1e9;
  for(int i=0;i<n;++i) if(P[i].y<P[YMinP].y) YMinP=i;
  for(int i=0;i<m;++i) if(Q[i].y>Q[YMaxQ].y) YMaxQ=i;
  P[n]=P[0]; Q[m]=Q[0];
  for (int i=0;i<n;++i) {
    while(tmp=((Q[YMaxQ+1]-P[YMinP+1])^(P[YMinP]-P[YMinP+1]))>((Q[YMaxQ]-P[YMinP+1])^(P[YMinP]-P[YMinP+1]))) YMaxQ=(YMaxQ+1)%m;
    if(tmp<0)ans=min(ans,PtToSegDis(P[YMinP],P[YMinP+1],Q[YMaxQ]));
    else ans=min(ans,TwoSegMinDis(P[YMinP],P[YMinP+1],Q[YMaxQ],Q[YMaxQ+1]));
    YMinP=(YMinP+1)%n;
  }
  return ans;
}
