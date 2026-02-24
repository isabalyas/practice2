#include "diophant_equation.h"

vector<long> continuedFrac(long num, long denom) {
    vector<long> coef;//коэффициент

    while (denom != 0) {
        long quotient = num / denom;
        coef.push_back(quotient);

        long temp = denom;
        denom = num - quotient * denom;
        num = temp;
    }

    return coef;
}

pair<long, long> solve_Diop(long a, long b, long c) {//diophantine

    tuple<long, long, long> next_tuple = ExtGcd(b % a, a);
    long gcd, x, y;

    gcd = get<0>(next_tuple);

    pair<long, long> res;

    if (c % gcd != 0) {//если c не делится gcd(a,b), то реш не сущ. 
        res = { 0, 0 };
        return res;
    }
    
    x = get<1>(next_tuple);
    y = get<2>(next_tuple);

    long k = c / gcd;
    long x0 = x * k;
    long y0 = y * k;
    res = { x0, y0 };
    return res;
}
