ld segDist(const Line &l1,const Line &l2){
  if(banana(l1.s,l1.e,l2.s,l2.e)) return 0;
  return min({
    ptSegDist(l1.s,l1.e,l2.s),ptSegDist(l1.s,l1.e,l2.e),
    ptSegDist(l2.s,l2.e,l1.s),ptSegDist(l2.s,l2.e,l1.e)
  });
}
