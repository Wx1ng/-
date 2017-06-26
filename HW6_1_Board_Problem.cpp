#include <iostream>
#include <cstring>
using namespace std;

int n, k;
int board[10][10];
bool usedRow[8];
bool usedCol[8];
int result = 0;

void DFS(int nLeft, int row, int col) {
	if (row + nLeft > n) return;
	if (nLeft == 0) {
		result++;
		return;
	}
	
	for (int i = row; i < n; i++) {
		if (usedRow[i]) continue;
		usedRow[i] = 1;
		for (int j = 0; j < n; j++) {
			if (usedCol[j]) continue;
			if (board[i][j] == '.') continue;
			usedCol[j] = 1;
			DFS(nLeft - 1, i + 1, j);
			usedCol[j] = 0;
		}
		usedRow[i] = 0;
	}
}

int main() {
	while (cin >> n >> k) {
		if (n == -1 && k == -1) break;
		for (int i = 0; i < n; i++) {
			cin.get();
			for (int j = 0; j < n; j++)
				board[i][j] = cin.get();
		}
		result = 0;
		DFS(k, 0, 0);
		cout << result << endl;
	}
	return 0;
}