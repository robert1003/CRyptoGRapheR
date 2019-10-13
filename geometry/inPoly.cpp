int inPoly(Pt p, vector<Pt> &v) {
	int n = v.size(), wn = 0;
	for(int i = 0 ; i < n ; ++i) {
		if(onseg(p, Line(v[i], v[(i+1)%n]))) return -1; // on edge
		int k = dcmp((v[(i+1)%n]-v[i])^(p-v[i]));
		int d1 = dcmp(v[i].y-p.y), d2 = dcmp(v[(i+1)%n].y-p.y);
		if(k > 0 && d1 <= 0 && d2 > 0) ++wn;
		if(k < 0 && d2 <= 0 && d1 > 0) --wn;
	}
	if(wn != 0) return 1;
	return 0;
}