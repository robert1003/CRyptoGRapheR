double volume(vector<Pt>& p,vector<Face> &trilist){
	double v=0;
	for(auto i:trilist) v+=(p[i.a]^p[i.b])*p[i.c];
	return abs(v)/6;
} // Each Face should point outwards
