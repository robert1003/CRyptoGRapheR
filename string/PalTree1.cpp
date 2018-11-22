const int MXN = 1000010;
struct PalT{
  int nxt[MXN][26],fail[MXN],len[MXN],cnt[MXN],num[MXN];
  int tot,lst,n;
  char s[MXN]={-1};
  int newNode(int l,int f){
    len[tot]=l,fail[tot]=f,cnt[tot]=num[tot]=0;
    memset(nxt[tot],0,sizeof(nxt[tot]));
    return tot++;
  }
  int get_fail(int x){
    while(s[n-len[x]-1]!=s[n]) x=fail[x];
    return x;
  }
  void push(){
    int c=s[n]-'a',np=get_fail(lst);
    if(!(lst=nxt[np][c])){
      lst=newNode(len[np]+2,nxt[get_fail(fail[np])][c]);
      nxt[np][c]=lst;
      num[lst]=num[fail[lst]]+1;
    }
    ++cnt[lst];
  }
  void init(const char *_s){
    tot=lst=n=0;
    newNode(0,1),newNode(-1,0);
    for(;_s[n];) s[n+1]=_s[n],++n,push();
    for(int i=tot-1;i>1;i--) cnt[fail[i]]+=cnt[i];
  }
}palt;
