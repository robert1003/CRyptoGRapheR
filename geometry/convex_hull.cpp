vector<Pt> convexhull(vector<Pt>& v) {
  sort(v.begin(), v.end());
  int n = unique(v.begin(), v.end()) - v.begin();
  vector<Pt> ch(n*2);

  int m = 0;
  for(int i = 0 ; i < n ; i++) {
    while(m > 1 && dcmp((ch[m-1]-ch[m-2])^(v[i]-ch[m-2])) <= 0) m--;
    ch[m++] = v[i];
  }
  int k = m;
  for(int i = n-2 ; i >= 0 ; i--) {
    while(m > k && dcmp((ch[m-1]-ch[m-2])^(v[i]-ch[m-2])) <= 0) m--;
    ch[m++] = v[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}