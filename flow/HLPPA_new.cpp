struct HLPPA{
	int n,m,s,t,ef[MAXN],ht[MAXN];
	int deg[MAXN],adj[MAXN][MAXN],res[MAXN][MAXN];
	int apt[MAXN],hcnt[MAXN*2],htodo;
	queue<int> ovque[MAXN*2];
	bool inque[MAXN];
	void init(int _n,int _s,int _t){
		n=_n; s=_s; t=_t;
		fill(deg,deg+n,0); memset(res,0,sizeof(res));
	}
	inline void add_edge(int u,int v,int c){
		adj[u][deg[u]++]=v; adj[v][deg[v]++]=u;
		res[u][v]+=c;
	}
	inline void preflow(){
		for(int i=0;i<n;i++)
			ht[i]=ef[i]=apt[i]=inque[i]=0;
		ht[s]=n; htodo=0;
		for(int i=0;i<deg[s];i++){
			int u=adj[s][i];
			ef[s]+=res[s][u]; ef[u]+=res[s][u];
			res[u][s]=ef[u]; res[s][u]=0;
		}
		for(int i=0;i<n*2;i++){
			hcnt[i]=0;
			while(!ovque[i].empty()) ovque[i].pop();
		}
		for(int i=0;i<n;i++){
			if(i==s||i==t) continue;
			if(ef[i])
				inque[i]=1,ovque[ht[i]].push(i);
			hcnt[ht[i]]++;
		}
		inque[s]=inque[t]=1;
	}
	inline void relabel(int v){
		int oldh=ht[v]; ht[v]=n*2;
		for(int i=0;i<deg[v];i++){
			int u=adj[v][i];
			if(res[v][u]) ht[v]=min(ht[v],ht[u]+1);
		}
		hcnt[oldh]--; hcnt[ht[v]]++;
		if(0<oldh&&oldh<n&&hcnt[oldh]==0){
			for(int i=0;i<n;i++){
				if(ht[i]>oldh&&ht[i]<n){
					hcnt[ht[i]]--;
					hcnt[ht[i]=n]++;
				}
			}
		}
		htodo=ht[v]; ovque[ht[v]].push(v); inque[v]=1;
	}
	inline void push(int v,int u){
		int f=min(ef[v],res[v][u]);
		ef[v]-=f; ef[u]+=f;
		res[v][u]-=f; res[u][v]+=f;
		if(!inque[u]){
			inque[u]=1;
			ovque[ht[u]].push(u);
		}
	}
	inline void discharge(int v){
		while(ef[v]){
			if(apt[v]==deg[v]){
				relabel(v); apt[v]=0;
				continue;
			}
			int u=adj[v][apt[v]];
			if(res[v][u]&&ht[v]==ht[u]+1) push(v,u);
			else apt[v]++;
		}
	}
	inline int flow(){
		preflow();
		while(htodo>=0){
			if(ovque[htodo].empty()){
				htodo--; continue;
			}
			int v=ovque[htodo].front();
			ovque[htodo].pop();
			inque[v]=0;
			discharge(v);
		}
		return ef[t];
	}
}flow;
