#include<bits/stdc++.h>
#define ll long long

using namespace std;

struct Dinic {
    static const int MXN = 200000;
    struct Edge { int v, f, re; };
    int n, s, t, level[MXN];
    vector<Edge> E[MXN];
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        for(int i = 0 ; i < n ; ++i) E[i].clear();
    }
    void add_edge(int u, int v, int f) {
        E[u].push_back({v, f, (int)E[v].size()});
        E[v].push_back({u, 0, (int)E[u].size() - 1});
    }
    bool BFS() {
        for(int i = 0 ; i < n ; ++i) level[i] = -1;
        queue<int> que;
        que.push(s);
        level[s] = 0;
        while(!que.empty()) {
            int u = que.front(); que.pop();
            for(auto &it : E[u]) {
                if(it.f > 0 && level[it.v] == -1) {
                    level[it.v] = level[u] + 1;
                    que.push(it.v);
                }
            }
        }
        return level[t] != -1;
    }
    int DFS(int u, int nf) {
        if(u == t) return nf;
        int res = 0;
        for(auto &it : E[u]) {
            if(it.f > 0 && level[it.v] == level[u] + 1) {
                int tf = DFS(it.v, min(nf, it.f));
                res += tf; nf -= tf; it.f -= tf;
                E[it.v][it.re].f += tf;
                if(nf == 0) return res;
            }
        }
        if(!res) level[u] = -1;
        return res;
    }
    int flow(int res=0) {
        while(BFS()) res += DFS(s, 2147483647);
        return res;
    }
} flow;

vector<string> a;
vector<vector<int>> id,Gx;
vector<pair<int,int>> rx,ry;
vector<bool> vx;
vector<int> mx,my;
const int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};

bool dfs(int x){
    if(vx[x]) return 0;
    vx[x]=1;
    for(int i:Gx[x]){
        if(my[i]==-1||dfs(my[i])){
            mx[x]=i; my[i]=x;
            return 1;
        }
    }
    return 0;
}

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int n,m; cin>>n>>m;
    a.resize(n);
    for(int i=0;i<n;i++) cin>>a[i];
    id.resize(n,vector<int>(m));
    int cx=0,cy=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='*') continue;
            if((i^j)&1) id[i][j]=cx++,rx.push_back({i,j});
            else id[i][j]=cy++,ry.push_back({i,j});
        }
    }
    Gx.resize(cx);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(~(i^j)&1) continue;
            if(a[i][j]=='*') continue;
            for(int k=0;k<4;k++){
                int ni=i+dx[k],nj=j+dy[k];
                if(ni<0||nj<0||ni==n||nj==m) continue;
                if(a[ni][nj]=='*') continue;
                Gx[id[i][j]].push_back(id[ni][nj]);
            }
        }
    }
    flow.init(cx+cy+2,cx+cy,cx+cy+1);
    for(int i=0;i<cx;i++){
        for(int j:Gx[i]) flow.add_edge(i,j+cx,1);
    }
    for(int i=0;i<cx;i++) flow.add_edge(flow.s,i,1);
    for(int i=0;i<cy;i++) flow.add_edge(i+cx,flow.t,1);
    cout<<cx+cy-flow.flow()<<"\n";
    for(int i=0;i<cx;i++){
        if(flow.level[i]!=-1){
            a[rx[i].first][rx[i].second]='C';
        }
    }
    for(int i=0;i<cy;i++){
        if(flow.level[i+cx]==-1){
            a[ry[i].first][ry[i].second]='C';
        }
    }
    for(int i=0;i<n;i++) cout<<a[i]<<"\n";
    return 0;
}
