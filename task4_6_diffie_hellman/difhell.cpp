#include <iostream>
#include "difhell.h"

using namespace std;

long DifHellKeyExchange(long p, long g, long a, long b) {

	long A = AXmodPlog(g, a, p);
	long B = AXmodPlog(g, b, p);

	cout << "Alice and Bob received their public keys" << endl;
	cout << "Alice and Bob exchanged their public keys" << endl;
	
    long sA = AXmodP(B, a, p);
	long sB = AXmodP(A, b, p);
	
    if (sA == sB) {
		cout << "Alice and Bob have successfully obtained single secret key" << endl;
		return sA;
	} else {
		cout << "Error: Occurred when calculate keys" << endl;
		return -1;
	}
}

long DifHellEveSim(long p, long g, long A, long B) {
	uint64_t a = 1;
	long E = AXmodPlog(g, a, p);
	while (E != A) {
		a++;
		E = AXmodPlog(g, a, p);
	}
	cout << "Eve found out Alice's private key" << endl;
	long s = AXmodP(B, a, p);
	cout << "Eva found out the shared private key" << endl;
	return s;
}
