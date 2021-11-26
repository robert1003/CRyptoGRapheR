ld ptSegDist(Pt &s,Pt &e,Pt &p){ // dis(Line(s,t),p)
	if(s==e) return norm(p-s);
	ld d=norm2(e-s),t=min(d,max(.0L,(p-s)*(e-s)));
	return norm((p-s)*d-(e-s)*t)/d;
}
