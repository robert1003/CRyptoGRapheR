void virtualTree(vector<int> v){
  graph.init(); vector<int> s; // v.push_back(root);
  sort(v.begin(),v.end(),[&](int i,int j){return dfn[i]<dfn[j];});
  v.resize(unique(v.begin(),v.end())-v.begin());
  for(int x:v){ // anc(x,y) iff x is an ancesor of y
    if(!s.empty()&&!anc(s.back(),x)){
      int p=lca(s.back(),x);
      while(d[s.back()]>d[p]){ // d: depth
        int y=s.back(); s.pop_back();
        if(s.empty()||d[s.back()]<d[p]) s.push_back(p);
        graph.addEdge(s.back(),y,d[y]-d[s.back()]);
      }
    }
    s.push_back(x);
  }
  for(int i=1;i<(int)s.size();i++)
    graph.addEdge(s[i-1],s[i],d[s[i]]-d[s[i-1]]);
}
