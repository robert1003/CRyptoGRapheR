// given n*m 0-1 matrix, find a set of rows s.t. 
// for each column, there's exactly one 1
const int N=1024,M=1024,NM=((N+2)*(M+2)) // row,col
bool A[N][M]; // n*m 0-1 matrix
bool used[N]; // answer: the row used
int id[N][M];
int L[NM],R[NM],D[NM],U[NM],C[NM],S[NM],ROW[NM];
void remove(int c){
  L[R[c]]=L[c];R[L[c]]=R[c];
  for(int i=D[c];i!=c;i=D[i])
    for(int j=R[i];j!=i;j=R[j]){
      U[D[j]]=U[j]; D[U[j]]=D[j]; S[C[j]]--;
    }
}
void resume(int c){
  for(int i=D[c];i!=c;i=D[i])
    for(int j=L[i];j!=i;j=L[j]){
      U[D[j]]=D[U[j]]=j; S[C[j]]++;
    }
  L[R[c]]=R[L[c]]=c;
}
bool dfs(){
  if(R[0]==0) return 1;
  int md=100000000,c;
  for(int i=R[0];i!=0;i=R[i]) if(S[i]<md){md=S[i]; c=i;}
  if(md==0) return 0;
  remove(c);
  for(int i=D[c];i!=c;i=D[i]){
    used[ROW[i]]=1;
    for(int j=R[i];j!=i;j=R[j]) remove(C[j]);
    if(dfs()) return 1;
    for(int j=L[i];j!=i;j=L[j]) resume(C[j]);
    used[ROW[i]]=0;
  }
  resume(c); return 0;
}
bool exact_cover(int n,int m){
  for(int i=0;i<=m;i++){
    R[i]=i+1; L[i]=i-1; U[i]=D[i]=i; S[i]=0; C[i]=i;
  }
  R[m]=0; L[0]=m; int t=m+1;
  for(int i=0;i<n;i++){
    int k=-1;
    for(int j=0;j<m;j++){
      if(!A[i][j]) continue;
      if(k==-1) L[t]=R[t]=t;
      else{ L[t]=k; R[t]=R[k]; }
      k=t; D[t]=j+1; U[t]=U[j+1];
      L[R[t]]=R[L[t]]=U[D[t]]=D[U[t]]=t;
      C[t]=j+1; S[C[t]]++; ROW[t]=i; id[i][j]=t++;
    }
  }
  for(int i=0;i<n;i++) used[i]=0;
  return dfs();
}
