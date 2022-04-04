const int N=5010,M=200010; const ll INF=(1ll<<55);
struct edge{
  int to; ll w;
  edge(int a=0,ll b=0):to(a),w(b){}
};
struct node{
  ll d; int u,next;
  node(ll a=0,int b=0,int c=0): d(a),u(b),next(c){}
}b[M];
struct DirectedGraphMinCycle{ // works in O(NM)
  vector<edge> g[N],grev[N]; ll dp[N][N],p[N],d[N],mu;
  bool inq[N]; int n,bn,bsz,hd[N];
  void b_insert(ll d,int u){
    int i=d/mu; if(i>=bn) return;
    b[++bsz]=node(d,u,hd[i]); hd[i]=bsz;
  }
  void init(int _n){
    n=_n; for(int i=1;i<=n;i++) g[i].clear();
  }
  void addEdge(int ai,int bi,ll ci)
  { g[ai].push_back(edge(bi,ci)); }
  ll solve(){
    fill(dp[0],dp[0]+n+1,0);
    for(int i=1;i<=n;i++){
      fill(dp[i]+1,dp[i]+n+1,INF);
      for(int j=1;j<=n;j++) if(dp[i-1][j]<INF){
        for(int k=0;k<(int)g[j].size();k++)
          dp[i][g[j][k].to]=min(dp[i][g[j][k].to],dp[i-1][j]+g[j][k].w);
      }
    }
    mu=INF; ll bunbo=1;
    for(int i=1;i<=n;i++) if(dp[n][i]<INF){
      ll a=-INF,b=1;
      for(int j=0;j<=n-1;j++) if(dp[j][i]<INF){
        if(a*(n-j)<b*(dp[n][i]-dp[j][i])){
          a=dp[n][i]-dp[j][i]; b=n-j;
        }
      }
      if(mu*b>bunbo*a) mu=a,bunbo=b;
    }
    if(mu<0) return -1; // negative cycle
    if(mu==INF) return INF; // no cycle
    if(mu==0) return 0;
    for(int i=1;i<=n;i++)
      for(int j=0;j<(int)g[i].size();j++) 
        g[i][j].w*=bunbo;
    memset(p,0,sizeof(p)); queue<int> q;
    for(int i=1;i<=n;i++){ q.push(i); inq[i]=true; }
    while(!q.empty()){
      int i=q.front(); q.pop(); inq[i]=false;
      for(int j=0;j<(int)g[i].size();j++){
        if(p[g[i][j].to]>p[i]+g[i][j].w-mu){
          p[g[i][j].to]=p[i]+g[i][j].w-mu;
          if(!inq[g[i][j].to]){
            q.push(g[i][j].to); inq[g[i][j].to]=true;
    } } } }
    for(int i=1;i<=n;i++) grev[i].clear();
    for(int i=1;i<=n;i++)
      for(int j=0;j<(int)g[i].size();j++){
        g[i][j].w+=p[i]-p[g[i][j].to];
        grev[g[i][j].to].push_back(edge(i,g[i][j].w));
      }
    ll mldc=n*mu;
    for(int i=1;i<=n;i++){
      bn=mldc/mu,bsz=0; memset(hd,0,sizeof(hd));
      fill(d+i+1,d+n+1,INF); b_insert(d[i]=0,i);
      for(int j=0;j<=bn-1;j++) 
        for(int k=hd[j];k;k=b[k].next){
          int u=b[k].u; ll du=b[k].d;
          if(du>d[u]) continue;
          for(int l=0;l<(int)g[u].size();l++) 
            if(g[u][l].to>i){
              if(d[g[u][l].to]>du+g[u][l].w){
                d[g[u][l].to]=du+g[u][l].w;
                b_insert(d[g[u][l].to],g[u][l].to);
        }   } } 
      for(int j=0;j<(int)grev[i].size();j++) 
        if(grev[i][j].to>i)
          mldc=min(mldc,d[grev[i][j].to]+grev[i][j].w);
    }
    return mldc/bunbo;
  }
} graph;
