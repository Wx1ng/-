#include <iostream>
#include <cstring>
using namespace std;

int N, M;
int W[3410];
int D[3410];
int F[12890];

int max(int x, int y) {
	return x > y ? x : y;
}

int main() {
	memset(F, 0, sizeof(F));
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		cin >> W[i];
		cin >> D[i];
	}
	for (int i = 1; i <= N; i++) {
		for (int j = M; j >= 1; j--) {
			if (W[i] <= j)
				F[j] = max(F[j], F[j - W[i]] + D[i]);
		}
	}
	cout << F[M] << endl;
}