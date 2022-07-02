/*target: max \sum_{j=1}^n A_{0,j}*x_j
condition: \sum_{j=1}^n A_{i,j}*x_j<=A_{i,0} |i=1~m
           x_j >= 0 |j=1~n */
template<class VDB> // VDB=vector<double>
VDB simplex(int m,int n,vector<VDB> a){
  vector<int> left(m+1),up(n+1);
  iota(left.begin(),left.end(),n);
  iota(up.begin(),up.end(),0);
  auto pivot=[&](int x,int y){
    swap(left[x],up[y]); 
    auto k=a[x][y];a[x][y]=1; vector<int> pos;
    for(int j=0;j<=n;++j){
      a[x][j]/=k;
      if(dcmp(a[x][j])!=0) pos.push_back(j);
    }
    for(int i=0;i<=m;++i){
      if(dcmp(a[i][y])==0||i==x) continue;
      k=a[i][y],a[i][y]=0;
      for(int j:pos) a[i][j]-=k*a[x][j];
    }
  };
  for(int x,y;;){
    for(int i=x=1;i<=m;++i) if(dcmp(a[i][0]-a[x][0])<0) x=i;
    if(dcmp(a[x][0])>=0) break;
    for(int j=y=1;j<=n;++j) if(dcmp(a[x][j]-a[x][y])<0) y=j;
    if(dcmp(a[x][y])>=0) return VDB(); // infeasible
    pivot(x,y);
  }
  for(int x,y;;){
    for(int j=y=1;j<=n;++j) if(dcmp(a[0][j]-a[0][y])>0) y=j;
    if(dcmp(a[0][y])<=0) break;
    x=-1;
    for(int i=1;i<=m;++i) if(dcmp(a[i][y])>0)
      if(x==-1||dcmp(a[i][0]/a[i][y]-a[x][0]/a[x][y])<0) x=i;
    if(x==-1) return VDB(); // unbounded
    pivot(x,y);
  }
  VDB ans(n+1);
  for(int i=1;i<=m;++i)
    if(left[i]<=n) ans[left[i]]=a[i][0];
  ans[0]=-a[0][0];
  return ans;
} // sometimes fails. check the condition and sum again
