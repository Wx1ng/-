#include <iostream>
using namespace std;

int main() {
	int m, n, r;
	while (cin >> m >> n) {	
		r = m < n ? m : n;
		while (m % n != 0) {
			r = m % n;
			m = n;
			n = r;
		}
		cout << r << endl;	
	}
	return 0;
}