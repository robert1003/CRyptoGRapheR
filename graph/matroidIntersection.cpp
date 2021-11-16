/* Matroid Definition:
 * 1. Empty set is ind. 2. Subset of ind. set is ind.
 * 3. If set A, B are ind. and |A| < |B|,
 *    there exists x in B\A s.t. A U {x} is ind.
 * Max Weighted Matroid Intersection: (memorize testInd)
 * Let vertex weight l(x) = (x is chosen ? w(x) : -w(x))
 * Find shortest aug. path with SPFA, based on minimize
 * tie(sum of l(x),number of edges) on the path. */
struct MatroidIntersection {
  int n;           // Elem: bool chosen, int p, info...
  vector<Elem> GS; // Ground Set.
  vector<int> indSet; // Current chosen ind. set
  bool testInd1(int add){} // indSet U {a}
  bool testInd1(int add,int removed){} // ind\{r}U{a}
  bool testInd2(int add){}
  bool testInd2(int add,int removed){}
  bool augment(){ // prepareInd1(), prepareInd2();
    for(auto &x:GS) x.p=-2; // init l,dis,len,inque
    int ep=-3;queue<int> q;
    for(int i=0;i<n;++i) if(!GS[i].chosen&&testInd1(i))
      GS[i].p=-1,q.push(i);
    while(!q.empty()){ // bfs -> SPFA
      int cur=q.front(); q.pop();
      if(GS[cur].chosen){ // SPFA dont check .p != -2
        for(int nxt=0;nxt<n;++nxt){
          if(GS[nxt].chosen or GS[nxt].p!=-2) continue;
          if(!testInd1(nxt,cur)) continue;
          GS[nxt].p=cur; q.push(nxt);
        }
      }else{ // SPFA record nearest ep, dont break
        if(testInd2(cur)){ ep=cur; break; } 
        for(auto nxt:indSet){
          if(GS[nxt].p!=-2 or !testInd2(cur,nxt)) 
            continue;
          GS[nxt].p=cur;q.push(nxt);
    } } }
    if(ep==-3) return false;
    do{ GS[ep].chosen^=1; ep=GS[ep].p; } while(ep!=-1);
    indSet.clear();
    for(int i=0;i<n;i++) if(GS[i].chosen)
        indSet.push_back(i);
    return true;
  }
  void solve(){ n=GS.size(); while(augment()); }
}MI;
