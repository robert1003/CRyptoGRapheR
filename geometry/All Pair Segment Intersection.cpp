struct event{
	Pt pt;int t,a,b; //sort by greater<pt.x>
	event(Pt &pt,int t,int a,int b=-1):pt(pt),t(t),a(a),b(b){}
};
vector<Line> lines; //must be filled
double cx=-1e9;
struct cmp{
	bool operator()(int a,int b){
		return lines[a].eval(cx)<lines[b].eval(cx);
	} //line.eval(x)=s.y+(e.y-s.y)*(x-s.x)/(e.x-s.x)
};
#define FI first
#define SE second
#define DEL(it) pq.erase(it->SE),it->SE=NULL;
#define UPD(cit,nit) \
Line A=lines[cit->FI],B=lines[nit->FI];\
if(cit->SE!=NULL) DEL(cit)\
Pt tmp=LLIntersect(A,B);\
if(!isnan(tmp.x)&&tmp.x>=cur.pt.x)\
cit->SE=pq.push({tmp,2,cit->FI,nit->FI});
#define INSF if(it!=s.begin()){UPD(prev(it),it)}
#define INSB if(next(it)!=s.end()){UPD(it,next(it))}
vector<Pt> AllPairLLIntersect(){
	__gnu_pbds::priority_queue<event> pq;
	map<int,__gnu_pbds::priority_queue<event>::point_iterator,cmp> s;
	for(int i=0;i<lines.size();i++){ //s.x < e.x
		pq.push({lines[i].s,0,i}),pq.push({lines[i].e,1,i});
	}
	vector<Pt> res;
	while(!pq.empty()){
		event cur=pq.top();pq.pop(); //cur.pt.x>=cx-eps
		cx=cur.pt.x-eps;
		if(cur.t==0){
			auto it=s.insert({cur.a,NULL}).FI;
			INSF;INSB;
		}
		else if(cur.t==1){
			auto it=s.lower_bound(cur.a); //it->FI==cur.a
			if(it->SE!=NULL) pq.erase(it->SE);
			s.erase(it++);
			if(it!=s.begin()&&it!=s.end()){UPD(prev(it),it)}
			else if(it!=s.begin()&&(--it)->SE!=NULL)DEL(it);
		}
		else{
			auto it=s.lower_bound(cur.a); //it->FI==cur.a
			res.push_back(cur.pt); //next(it)->FI==cur.b
			s.erase(it++);
			if(it->SE!=NULL) pq.erase(it->SE);
			s.erase(it++);
			cx+=eps*2;
			it=s.insert(it,{cur.a,NULL});INSB;
			it=s.insert(it,{cur.b,NULL});INSF;
		} //next(it)->FI==cur.a
		cx=cur.pt.x;
	}
	return res;
}
