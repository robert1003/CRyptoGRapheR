pair<ld,pair<Pt,Pt>> hullDiameter(const vector<Pt> &S){
	int n=S.size(),j=n<2?0:1; // given a convex hull S
	pair<ld,pair<Pt,Pt>> res({0,{S[0],S[0]}});
	for(int i=0;i<j;i++) for(;;j=(j+1)%n){
			res=max(res,{norm2((S[i]-S[j])),{S[i],S[j]}});
			if(((S[(j+1)%n]-S[j])^(S[i+1]-S[i]))>=0)
				break;
		}
	return res; // {max_dis,{pt1,pt2}}
}
