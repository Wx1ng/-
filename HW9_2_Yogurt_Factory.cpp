#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N, S;
int C[10000], Y[10000];
long long sum;

int main() {
	memset(C, 0, sizeof(C));
	memset(Y, 0, sizeof(Y));
	cin >> N >> S;
	for (int i = 0; i < N; i++)
		cin >> C[i] >> Y[i];
	sum = 0;
	for (int i = 0; i < N; i++) {
		int unitPrice = C[i];	//×îµÍµ¥¼Û
		int j;
		for (j = 0; j < i; j++) {
			int x = C[j] + S*(i - j);
			if (x < C[i])
				unitPrice = x < unitPrice ? x : unitPrice;
		}
		sum += unitPrice * Y[i];
	}
	cout << sum << endl;
	return 0;
}