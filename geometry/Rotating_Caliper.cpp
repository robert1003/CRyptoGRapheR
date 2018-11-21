// use on convexhull
double diameter(vector<Pt>& p) {
    n = p.size();
    if(n == 1) return 0;
    if(n == 2) return norm(p[0]-p[1]);
    p.push_back(p[0]);
    double maxdis = 0.0;
    for(int u = 0, v = 1 ; u < n ; u++) {
        while(true) {
            int diff = dcmp((p[u+1]-p[u])^(p[v+1]-p[v]));
            if(diff <= 0) {
                maxdis = max(maxdis, norm(p[v]-p[u]));
                if(diff == 0) maxdis = max(maxdis, norm(p[v+1]-p[u]));
                break;
            }
            v = (v+1)%n;
        }
    }
    v.pop_back();
    return maxdis;
}
