//n,Dinic::flow must be filled
//result:e[u][v]=u-v mincut;p[u]:u's parent on cut tree
int n,e[MXN][MXN],p[MXN];
void gomory_hu(){
  fill(p,p+n,0); fill(e[0],e[n],INF);
  for(int s=1;s<n;s++){
    int t=p[s]; Dinic F; F.init(n,s,t);
    copy(flow.E,flow.E+MXN,F.E); int tmp=F.flow();
    for(int i=0;i<s;i++)
      e[s][i]=e[i][s]=min(tmp,e[t][i]);
    for(int i=s+1;i<n;i++) 
      if(p[i]==t&&F.level[i]!=-1) p[i]=s;
  }
}
