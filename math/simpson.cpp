template<class F>
ld quad(ld a, ld b, F f, const int n = 1000) {
    ld h = (b-a)/2/n, v=f(a)+f(b);
    for(int i = 1; i < n*2; ++i)
        v += f(a+i*h) * (i&1 ? 4 : 2);
    return v * h / 3;
}
