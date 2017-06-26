#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N, C;
long long X[100000];

bool check(long int interval) {
	int i = 0;	//当前节点
	int cows = 1;	//当前入棚牛数
	for (int j = 1; j < N; j++) {
		if (X[j] - X[i] >= interval) {
			i = j;
			cows++;
		}
		if (cows >= C)
			break;
	}
	return cows >= C;
}

int main() {
	cin >> N >> C;
	for (int i = 0; i < N; i++)
		cin >> X[i];
	sort(X, X + N);
	//cout << X[2] << endl;
	long long left = X[0];
	long long right = X[N - 1] - X[0];
	long long mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (check(mid))
			left = mid + 1;
		else
			right = mid - 1;
	}
	cout << right << endl;
	return 0;
}
