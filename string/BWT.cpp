const int SIGMA=26; const char BASE='a';
struct BurrowsWheeler{
  vector<int> v[SIGMA];
  void BWT(char* ori,char* res){
    // make ori -> ori+ori and then build suffix array
  }
  void iBWT(char* ori,char* res){
    for(int i=0;i<SIGMA;i++) v[i].clear();
    int len=strlen(ori); vector<int> a;
    for(int i=0;i<len;i++) v[ori[i]-BASE].push_back(i);
    for(int i=0,ptr=0;i<SIGMA;i++)
      for(auto j:v[i]){
        a.push_back(j); ori[ptr++]=BASE+i;
      }
    for(int i=0,ptr=0;i<len;i++){
      res[i]=ori[a[ptr]]; ptr=a[ptr];
    }
    res[len]=0;
  }
}bwt;
