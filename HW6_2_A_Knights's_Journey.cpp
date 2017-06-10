#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

bool board[9][9];
int p, q;
char qAlpha[27] = { 0,'A','B','C','D','E','F','G','H','I','J','K','L','M','N',
					'O','P','Q','R','S','T','U','V','W','X','Y','Z' };
int nVisited;
struct square {
	int row; int col;
	square(int r, int c) :row(r), col(c) {}
};
vector<square> path;

bool DFS(int row, int col) {
	nVisited++;
	//board[row][col] = 1;
	if (nVisited == p*q) return true;
	if (!board[row - 2][col - 1] && row - 2 > 0 && col - 1 > 0) {
		board[row - 2][col - 1] = 1;
		if (DFS(row - 2, col - 1)) {
			path.insert(path.begin(), square(row - 2, col - 1));
			return true;
		}
		else {
			board[row - 2][col - 1] = 0;
			nVisited--;
		}
	}
	if (!board[row - 2][col + 1] && row - 2 > 0 && col + 1 <= p) {
		board[row - 2][col + 1] = 1;
		if (DFS(row - 2, col + 1)) {
			path.insert(path.begin(), square(row - 2, col + 1));
			return true;
		}
		else {
			board[row - 2][col + 1] = 0;
			nVisited--;
		}
	}
	if (!board[row - 1][col - 2] && row - 1 > 0 && col - 2 > 0) {
		board[row - 1][col - 2] = 1;
		if (DFS(row - 1, col - 2)) {
			path.insert(path.begin(), square(row - 1, col - 2));
			return true;
		}
		else {
			board[row - 1][col - 2] = 0;
			nVisited--;
		}
	}
	if (!board[row - 1][col + 2] && row - 1 > 0 && col + 2 <= p) {
		board[row - 1][col + 2] = 1;
		if (DFS(row - 1, col + 2)) {
			path.insert(path.begin(), square(row - 1, col + 2));
			return true;
		}
		else {
			board[row - 1][col + 2] = 0;
			nVisited--;
		}
	}
	if (!board[row + 1][col - 2] && row + 1 <= q && col - 2 > 0) {
		board[row + 1][col - 2] = 1;
		if (DFS(row + 1, col - 2)) {
			path.insert(path.begin(), square(row + 1, col - 2));
			return true;
		}
		else {
			board[row + 1][col - 2] = 0;
			nVisited--;
		}
	}
	if (!board[row + 1][col + 2] && row + 1 <= q && col + 2 <= p) {
		board[row + 1][col + 2] = 1;
		if (DFS(row + 1, col + 2)) {
			path.insert(path.begin(), square(row + 1, col + 2));
			return true;
		}
		else {
			board[row + 1][col + 2] = 0;
			nVisited--;
		}
	}
	if (!board[row + 2][col - 1] && row + 2 <= q && col - 1 > 0) {
		board[row + 2][col - 1] = 1;
		if (DFS(row + 2, col - 1)) {
			path.insert(path.begin(), square(row + 2, col - 1));
			return true;
		}
		else {
			board[row + 2][col - 1] = 0;
			nVisited--;
		}
	}
	if (!board[row + 2][col + 1] && row + 2 <= q && col + 1 <= p) {
		board[row + 2][col + 1] = 1;
		if (DFS(row + 2, col + 1)) {
			path.insert(path.begin(), square(row + 2, col + 1));
			return true;
		}
		else {
			board[row + 2][col + 1] = 0;
			nVisited--;
		}
	}
	return false;
}

int main() {
	int n;
	int caseNum = 0;
	cin >> n;
	while (n--) {
		caseNum++;
		cin >> p >> q;;
		for (int i = 1; i <= q; i++) {
			for (int j = 1; j <= p; j++)
				board[i][j] = 0;
		}
		nVisited = 0;
		path.clear();
		for (int i = 1; i <= q; i++) {
			for (int j = 1; j <= p; j++) {
				board[i][j] = 1;
				if (DFS(i, j)) {
					path.insert(path.begin(), square(i, j));
					break;
				}
				else {
					board[i][j] = 0;
					nVisited--;
				}
			}
			if (nVisited == p*q)
				break;
		}
		cout << "Scenario #" << caseNum << ":" << endl;
		if (nVisited == p*q) {
			for (int i = 0; i < path.size(); i++)
				cout << qAlpha[path[i].row] << path[i].col;
			cout << endl;
		}
		else
			cout << "impossible" << endl;

		cout << endl;
	}
	
	
	
	return 0;
}

