typedef vector<int> vi; typedef pair<int,int> pii;
vi edgeColoring(int n,vector<pii> eds){ // 0-based
	vi cc(n+1),ret(eds.size()),fan(n),free(n),loc;
	for(pii e:eds) ++cc[e.first],++cc[e.second];
	int u,v,ncols=*max_element(cc.begin(),cc.end())+1;
	vector<vi> adj(n,vi(ncols,-1));
	for(pii e:eds){
		tie(u,v)=e; fan[0]=v; loc.assign(ncols,0);
		int at=u,end=u,d,c=free[u],ind=0,i=0;
		while(d=free[v],!loc[d]&&(v=adj[u][d])!=-1)
			loc[d]=++ind,cc[ind]=d,fan[ind]=v;
		cc[loc[d]]=c;
		for(int cd=d;at!=-1;cd^=c^d,at=adj[at][cd])
			swap(adj[at][cd],adj[end=at][cd^c^d]);
		while(adj[fan[i]][d]!=-1){
			int left=fan[i],right=fan[++i],e=cc[i];
			adj[u][e]=left; adj[left][e]=u;
			adj[right][e]=-1; free[right]=e;
		}
		adj[u][d]=fan[i]; adj[fan[i]][d]=u;
		for(int y:{fan[0],u,end})
			for(int& z=free[y]=0;adj[y][z]!=-1;z++);
	}
  for(int i=0;i<(int)eds.size();i++)
		for(tie(u,v)=eds[i];adj[u][ret[i]]!=v;) ++ret[i];
	return ret; // color (0~max_deg) of each edge (O(NM))
} // max_deg coloring for bipartite graph: repeatly
// find a matching containing all max_deg vertices,
// color those edges with a color and remove them.
// use bounded flow to force to use all max_deg vertices
