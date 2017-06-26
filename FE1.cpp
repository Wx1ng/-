#include <iostream>
#include <cstring>
using namespace std;

int rubbSum[1025][1025];

int main() {
	int T;
	cin >> T;
	while (T--) {
		memset(rubbSum, 0, sizeof(rubbSum));
		int d, n;
		cin >> d >> n;
		while (n--) {		
			int x, y, i;
			cin >> x >> y >> i;
			int left = 0 > x - d ? 0 : x - d;
			int right = 1024 < x + d ? 1024 : x + d;
			int top = 0 > y - d ? 0 : y - d;
			int bottom = 1024 < y + d ? 1024 : y + d;

			for (int a = left; a <= right; a++) {
				for (int b = top; b <= bottom; b++)
					rubbSum[a][b] += i;
			}
		}
		int maxNum = 0, maxSum = 0, curSum = 0;
		for (int p = 0; p < 1025; p++) {
			for (int q = 0; q < 1025; q++) {
				curSum = rubbSum[p][q];
				if (curSum > maxSum) {
					maxSum = curSum;
					maxNum = 1;
				}
				else if (curSum == maxSum)
					maxNum++;
				else
					continue;
			}
		}
		cout << maxNum << ' ' << maxSum << endl;
	}
	return 0;
}