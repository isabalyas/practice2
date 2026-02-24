#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>

#include "axmodp.h"
#include "euclid_combined.h"
#include "diophant_equation.h"
#include "difhell.h"
#include "gronsfeld.h"

using namespace std;

void task1 (uint64_t A, uint64_t X, uint64_t P)
{
    uint64_t res;
    if (!isPrime(P)){
        cout << "Error, 'p' may be a prime number" << endl;
    }
    else{
        res = AXmodPlog(A, X, P);
        cout << "ответ через двоичный алгоритм: " << A << "^" << X << " mod " << P << " = " << res << endl;
        
        res = AXmodP (A, X, P);
        cout << "ответ через классический алгоритм: "<<A << "^" << X << " mod " << P << " = " << res << endl;
    }
}

void task5(long a, long b, long c)
{
    pair<long, long> resDio;
    resDio = solve_Diop(a, b, c);
    if (resDio.first == 0 && resDio.second == 0) {
        cout << "This Diophantine equation has no integer solutions." << endl;
    }
    else if (a * resDio.first + b * resDio.second == c) {
        cout << a << "*" << resDio.first << " + " << b << "*" << resDio.second << " = " << c << endl;
    }
    else if (a * resDio.second + b * resDio.first == c) {
    cout << a << "*" << resDio.second << " + " << b << "*" << resDio.first << " = " << c << endl;
    }
    else {
        cout << "This Diophantine equation is solved incorrectly." << endl;
        cout << a << "*" << resDio.first << " + " << b << "*" << resDio.second << " = " << c << endl;
    }
}

int main()
{
    int i = 0;
    string strKey;
    long secretKey;
    long a, b, c;
    tuple<long, long, long> resTup;
    uint64_t A, X, P;
    
loop:
    cout << "\n Input number to select option:\
        \n 1 - Calculate a^x mod p (Task 1)\
        \n 2 - Calculate Expanded euclid and reciprocal Number (Task 2 and Task 3)\
        \n 3 - Diffie-hellman and cipher file (Task 4 and Task 6)\
        \n 4 - Diophantine (Task 5) \
        \n Any other - exit\
        \n >>> ";
    cin >> i;
    switch (i)
    {
    case 1:
        cout << "Please, input numbers A, X, P (for a^x mod p)" << endl;
        cin >> A >> X >> P;
        task1(A, X, P);
        goto loop;
        break;

    case 2:
        cout << "Please, input numer A and B for euclid alghorithm" << endl;
        cin >> a >> b;
        resTup = ExtGcd(a, b);
        cout << "gcd: " << get<0>(resTup) << " u: " << get<1>(resTup) << " v: " << get<2>(resTup) << endl;
        cout << "Reciprocal number: " << reciprocalNumber(a, b) << endl;
        cout << "Mutally prime: " << mutPrime(a, b) << endl;
        goto loop;
        break;
   
    case 3:
        secretKey = DifHellKeyExchange(703753, 253789, 29441, 38576);
        cout << secretKey << endl;
        cout << DifHellEveSim(703753, 253789, 625121, 541443) << endl;

        strKey = to_string(secretKey);

        encrypt_file("From/img.png", "To/encrypted.bin", strKey);
        decrypt_file("To/encrypted.bin", "Res/decrypted.png", strKey);
        goto loop;
        break;

    case 4:
        cout << "Please, input numbers A, B, C for diophantine (X1*A + X2* B = C)" << endl;
        cin >> a >> b >> c;
        task5(a, b, c);
        goto loop;
        break;


    default:
        return 0;
    }
}
