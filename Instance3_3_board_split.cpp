#include <iostream>
#include <cstring>
#include <algorithm>
#include <iomanip>
using namespace std;

int s[9][9];	//每个格子的分数
int sum[9][9];	//（1,1）到（i，j）的矩形分数之和
int res[15][9][9][9][9];	//fun的记录表

int calSum(int x1, int y1, int x2, int y2){
	return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}

int fun(int n, int x1, int y1, int x2, int y2){
	int t, a, b, MIN = 10000000;
	if (res[n][x1][y1][x2][y2] != -1)
		return res[n][x1][y1][x2][y2];
	if (n == 1){
		t = calSum(x1, y1, x2, y2);
		res[n][x1][y1][x2][y2] = t*t;
		return t*t;
	}

	for (int i = x1; i < x2; i++){
		a = calSum(x1, y1, i, y2);
		b = calSum(i + 1, y1, x2, y2);

		t = min(a*a + fun(n - 1, i + 1, y1, x2, y2), b*b + fun(n - 1, x1, y1, i, y2));
		if (MIN > t)
			MIN = t;
	}
	for (int j = y1; j < y2; j++){
		a = calSum(x1, y1, x2, j);
		b = calSum(x1, j + 1, x2, y2);

		t = min(a*a + fun(n - 1, x1, j + 1, x2, y2), b*b + fun(n - 1, x1, y1, x2, j));
		if (MIN > t)
			MIN = t;
	}
	
	res[n][x1][y1][x2][y2] = MIN;
	return MIN;
}

int main(){
	memset(sum, 0, sizeof(sum));
	memset(res, -1, sizeof(res));
	int n;
	cin >> n;
	for (int i = 1; i < 9; i++){
		for (int j = 1, rowsum = 0; j < 9; j++) {
			cin >> s[i][j];
			rowsum += s[i][j];
			sum[i][j] += sum[i - 1][j] + rowsum;
		}
	}

	double result = sqrt(fun(n, 1, 1, 8, 8) / float(n) - sum[8][8] * sum[8][8] / float(n*n));
	cout << fixed << setprecision(3) << result << endl;
	
	return 0;
}