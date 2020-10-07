#include<bits/stdc++.h>
#define ll long long

using namespace std;

#define ld long double

struct Point {
    ld x, y;
};

Point P[2002];

priority_queue<pair<ld, int>> PQ[2002];

const ld pi = acos(-1.0l);

inline ld sq(const ld x) {
    return x * x;
}

inline ld dis2(const Point& a, const Point& b)  {
    return sq(a.x - b.x) + sq(a.y - b.y);
}

bool dead[2002];
ld adjDead[2002];

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; ++i)
        cin >> P[i].x >> P[i].y;

    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n; ++j) {
            if(j == i) continue;
            PQ[i].push({-dis2(P[i], P[j]), j});
        }

    for(int i = 1; i <= n; ++i)
        adjDead[i] = 1e18;

    int cur = n;
    ld lastr = 0;
    ld ans = 0;
    while(1) {
        if(cur == 0) break;
        ld minR = 1e18;

        for(int i = 1; i <= n; ++i) {
            if(dead[i]) continue;
            if(PQ[i].size()) {
                auto x = PQ[i].top();
                while(!PQ[i].empty() and dead[x.second])  {
                    PQ[i].pop();
                    x = PQ[i].top();
                }
                if(!dead[x.second]) {
                    minR = min(minR, -x.first / 4);
                }
            }

            minR = min(minR, adjDead[i]);
        }

        ans += cur * pi * (minR - lastr);

        for(int i = 1; i <= n; ++i) {
            if(dead[i]) continue;
            bool flag = 0;
            if(fabs(adjDead[i] - minR) <= 1e-6) flag = 1;
            if(PQ[i].size()) {
                auto x = PQ[i].top();
                while(!PQ[i].empty() and dead[x.second])  {
                    PQ[i].pop();
                    x = PQ[i].top();
                }
                if(!dead[x.second]) {
                    if(fabs(-x.first / 4 - minR) <= 1e-6) flag = 1;
                }
            }

            if(flag) {
                dead[i] = 1;
                --cur;
                for(int j = 1; j <= n; ++j) {
                    if(dead[j]) continue;
                    adjDead[j] = min(adjDead[j], sq(sqrt(dis2(P[i], P[j])) - sqrt(minR)));
                }
            }
        }



        lastr = minR;
    }

    cout << fixed;
    cout.precision(12);
    cout << ans << '\n';
    return 0;
}
