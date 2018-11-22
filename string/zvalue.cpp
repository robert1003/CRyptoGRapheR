void z_value(char *s,int len,int *z){
  z[0]=len;
  for(int i=1,l=0,r=0;i<len;i++){
    z[i]=i<r?(i-l+z[i-l]<z[l]?z[i-l]:r-i):0;
    while(i+z[i]<len&&s[i+z[i]]==s[z[i]]) ++z[i];
    if(i+z[i]>r) l=i,r=i+z[i];
  }
}
