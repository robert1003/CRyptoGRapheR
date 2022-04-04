void dfs(int i){
  V[i]=low[i]=++ts,stk[top++]=i,instk[i]=1;
  for(auto x:E[i]){
    if(!V[x])dfs(x),low[i]=min(low[i],low[x]);
    else if(instk[x])low[i]=min(low[i],V[x]);
  }
  if(V[i]==low[i]){
    int j;
    do{j=stk[--top],instk[j]=0,scc[j]=i;
    }while(j!=i);
  }
}
