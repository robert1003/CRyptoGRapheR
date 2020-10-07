#include<bits/stdc++.h>
#define ll long long

using namespace std;

int main(){
    cin.tie(0); ios::sync_with_stdio(0);
    ll p, q, r; cin >> p >> q >> r;
    ll xu = p * 3 - q * 2 + r, xd = (p + r) * 2;
    ll yu = p + q * 2 - r, yd = (p + r) * 2;
    if(xu <= 0 || yu <= 0 || xd <= 0 || yd <= 0) {
        cout << "-1\n";
    }
    else {
        ll gx = __gcd(xu, xd); xu /= gx; xd /= gx;
        ll gy = __gcd(yu, yd); yu /= gy; yd /= gy;
        if(xu >= xd || yu >= yd) {
            cout << "-1\n";
        }
        else {
            cout << xu << "/" << xd << ' ' << yu << "/" << yd << '\n';
        }
    }


    return 0;
}
