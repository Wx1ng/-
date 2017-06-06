#include <iostream>
using namespace std;

const static int inf = 0x7FFFFFFF;

int cur_count(int pting[][20], int pt[][20], int n){
	int count = 0;
	int row, col;
	for (row = 1; row < n; row++){
		for (col = 1; col <= n; col++){
			pt[row + 1][col] = (pting[row][col] + pt[row][col] + 
				pt[row - 1][col] + pt[row][col - 1] + pt[row][col + 1] + 1) % 2;
		}
	}
	for (col = 1; col <= n; col++){
		//数字相同时，代表该位置为0，即白色
		if (pting[n][col] == (pt[n][col - 1] + pt[n][col] + pt[n][col + 1] + pt[n - 1][col]) % 2)
			return inf;
	}
	for (row = 1; row <= n; row++){
		for (col = 1; col <= n; col++){
			if (pt[row][col] == 1)
				count++;
		}
	}
	return count;
}
void enumerate(int pting[][20], int pt[][20], int n, int& min_count){
	int col = 1;
	int count;
	bool Stop = true;
	while (true){
		//pt[1][1]++;
		//col = 1;
		while (pt[1][col] > 1){
			pt[1][col] = 0;
			col++;
			pt[1][col]++;
		}
		count = cur_count(pting, pt, n);
		if (count < min_count)
			min_count = count;
		for (int i = n; i > 0; i--){
			if (!(Stop && pt[1][i]))
				break;
			if (i == 1)
				return;
		}
		pt[1][1]++;
		col = 1;
	}
}
int main(){
	int t;
	cin >> t;
	while (t--){
		int n;
		char c;
		int painting[20][20] = { 0 };
		int paint[20][20] = { 0 };
		cin >> n;
		cin.get();
		for (int i = 1; i <= n; i++){
			for (int j = 1; j <= n; j++){
				cin >> c;
				if (c == 'y')
					painting[i][j] = 1;
			}
		}
		int min_count = inf;
		enumerate(painting, paint, n, min_count);
		if (min_count == inf){
			cout << "inf" << endl;
			continue;
		}
		cout << min_count << endl;
	}
	return 0;
}