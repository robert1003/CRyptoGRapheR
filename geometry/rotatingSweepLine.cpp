void rotatingSweepLine(vector<Pt> &ps){
  int n=int(ps.size()); vector<int> id(n),pos(n);
  vector<pair<int,int>> line(n*(n-1)/2); int m=0;
  for(int i=0;i<n;++i) 
    for(int j=i+1;j<n;++j) line[m++]=make_pair(i,j);
  sort(line.begin(),line.end(),[&](const pair<int,int> &a,const pair<int,int> &b)->bool{
    if(ps[a.first].x==ps[a.second].y) return 0;
    if(ps[b.first].x==ps[b.second].y) return 1;
    return (double)(ps[a.first].y-ps[a.second].y)/(ps[a.first].x-ps[a.second].x)<(double)(ps[b.first].y-ps[b.second].y)/(ps[b.first].x-ps[b.second].x);
  }); // change to use multiply for better precision
  for(int i=0;i<n;++i) id[i]=i;
  sort(id.begin(),id.end(),[&](const int &a,const int &b){ return ps[a]<ps[b]; }); // tie(x,y)
  for(int i=0;i<n;++i) pos[id[i]]=i;
  for(int i=0;i<m;++i){ pair<int,int> l=line[i];
    // do something: Line(ps[l.first],ps[l.second]);
    // id: sorted id of ps w.r.t dis(l,p) (dis<0 for points in -y direction); pos[id[i]]=i;
    tie(pos[l.first],pos[l.second],id[pos[l.first]],id[pos[l.second]])=make_tuple(pos[l.second],pos[l.first],l.second,l.first);
  }
}
