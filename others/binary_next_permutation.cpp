ull next_perm(ull v){
  ull t=v|(v-1);
  return (t+1)|(((~t&-~t)-1)>>(__builtin_ctzll(v)+1));
}
