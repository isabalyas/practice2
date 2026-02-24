#include <vector>
#include <iostream>
#include <cstdint>
#include "axmodp.h"
#include <cmath>

using namespace std;

uint64_t AXmodP(uint64_t a, uint64_t x, uint64_t p)
{
    uint64_t res = 1;
    for (uint64_t i = 0; i < x; i++) {
        res = (res * a) % p;
    }
    return res;
}

uint64_t AXmodPlog(uint64_t a, uint64_t x, uint64_t p) {
    if (x == 0) return 1;
    if (p == 1) return 0;

    vector<short> binX;
    uint64_t tempX = x;
    while (tempX != 0) {
        binX.push_back(tempX % 2);
        cout << "x: " << tempX << "%2 = " << tempX % 2 << endl;
        tempX /= 2;
    }

    uint64_t result = 1;
    uint64_t curPower = a % p;

    cout << "first curPower = a % p : " << a << " % " << p << " = " << curPower << endl;

    for (size_t i = 0; i < binX.size(); ++i) {
        if (binX[i] == 1) {
            cout << "calc. result: (result * curPower) % p : (" << result << " * " << curPower << ") % " << p << " = ";
            result = (result * curPower) % p;
            cout << result << endl;
        }
        cout << "calc. curPower: (curPower^2) % p : (" << curPower << " * " << curPower << ") % " << p << " = ";
        curPower = (curPower * curPower) % p;
        cout << curPower << endl;
    }

    return result;
}

bool isPrime(uint64_t p)
{
    if (p % 2 == 0 || p % 3 == 0 || p <= 1) return false;
    

    uint64_t sqr_root_n = static_cast<uint64_t>(sqrt(p)) + 1;
    uint64_t maxI = (sqr_root_n + 1) / 6;

    for (uint64_t i = 1; i < maxI; i++) {
        uint64_t dividerMinusOne = 6 * i - 1;
        uint64_t dividerPlusOne = 6 * i + 1;

        if (dividerMinusOne <= sqr_root_n) {
            if (p % dividerMinusOne == 0)
                return false;
        }
        if (dividerPlusOne <= sqr_root_n) {
            if (p % dividerPlusOne == 0)
                return false;
        }
    }
    return true;
}
