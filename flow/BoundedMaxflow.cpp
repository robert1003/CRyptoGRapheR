// Max flow with lower/upper bound on edges
// use with ISAP
int in[N],out[N],l[M],r[M],a[M],b[M];
int solve(int n, int m, int s, int t){
  flow.init( n );
  for( int i = 0 ; i < m ; i ++ ){
    in[ r[ i ] ] += a[ i ];
    out[ l[ i ] ] += a[ i ];
    flow.addEdge( l[ i ] , r[ i ] , b[ i ] - a[ i ] );
    // flow from l[i] to r[i] must in [a[ i ], b[ i ]]
  }
  int nd = 0;
  for( int i = 0 ; i <= n ; i ++ ){
    if( in[ i ] < out[ i ] ){
      flow.addEdge( i , flow.t , out[ i ] - in[ i ] );
      nd += out[ i ] - in[ i ];
    }
    if( out[ i ] < in[ i ] )
      flow.addEdge( flow.s , i , in[ i ] - out[ i ] );
  }
  // original sink to source
  flow.addEdge( t , s , INF );
  if( flow.solve() != nd ) return -1; // no solution
  int ans = flow.G[ s ].back().c; // source to sink
  flow.G[ s ].back().c = flow.G[ t ].back().c = 0;
  // take out super source and super sink
  for(size_ti=0;i<flow.G[flow.s].size();i++){
    flow.G[ flow.s ][ i ].c = 0;
    Maxflow::Edge &e = flow.G[ flow.s ][ i ];
    flow.G[ e.v ][ e.r ].c = 0;
  }
  for(size_ti=0;i<flow.G[flow.t].size();i++){
    flow.G[ flow.t ][ i ].c = 0;
    Maxflow::Edge &e = flow.G[ flow.t ][ i ];
    flow.G[ e.v ][ e.r ].c = 0;
  }
  flow.addEdge( flow.s , s , INF );
  flow.addEdge( t , flow.t , INF );
  flow.reset(); // set iter,d,gap to 0
  return ans + flow.solve();
}
