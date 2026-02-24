#include "euclid_alg.h"

using namespace std;

long gcd(long a, long b) {
    while (b != 0) {
        long c = b;
        b = a % b;
        a = c;
    }
    return a;
}

tuple<long, long, long> ExtGcd(long a, long b) {
    if (a == 0) {
        return std::make_tuple(b, 0, 1);
    }

    tuple<long, long, long> nextTup = ExtGcd(b % a, a);
    long gcd, x1, y1;
    gcd = get<0>(nextTup);
    x1 = get<1>(nextTup);
    y1 = get<2>(nextTup);

    long x = y1 - (b / a) * x1;
    long y = x1;

    return std::make_tuple(gcd, x, y);
}

long reciprocalNumber(long a, long m) {
    tuple<long, long, long> resTup = ExtGcd(a, m);
    long gcd = get<0>(resTup);
    long x = get<1>(resTup);
    if (gcd != 1) {
        return 0;
    }
    return (x % m + m) % m;
}

bool mutPrime(long a, long b) {
    return gcd(a, b) == 1;
}
