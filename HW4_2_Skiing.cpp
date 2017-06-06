#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int R, C;
int area[101][101];
int L[101][101] = { 1 };

struct Lx {
	int i, j, height;
	bool operator < (const Lx& l) const { return height > l.height; }
	Lx(int ii = 0, int jj = 0, int h = 0) :i(ii), j(jj), height(h) {}
};
priority_queue<Lx> qLx;

int main() {
	int result = 0;
	cin >> R >> C;
	//memset(L, 1, sizeof(L));
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> area[i][j];
			qLx.push(Lx(i, j, area[i][j]));
		}
	}
	Lx lx;
	while (!qLx.empty()) {
		lx = qLx.top();
		int max_s = L[lx.i][lx.j];
		if (lx.i > 0)	//ио
			if (lx.height > area[lx.i - 1][lx.j] && max_s < L[lx.i - 1][lx.j] + 1)
				max_s = L[lx.i - 1][lx.j] + 1;
		if (lx.i < R - 1)	//об
			if (lx.height > area[lx.i + 1][lx.j] && max_s < L[lx.i + 1][lx.j] + 1)
				max_s = L[lx.i + 1][lx.j] + 1;
		if (lx.j > 0)	//вС
			if (lx.height > area[lx.i][lx.j - 1] && max_s < L[lx.i][lx.j - 1] + 1)
				max_s = L[lx.i][lx.j - 1] + 1;
		if (lx.j < C - 1)	//ср
			if (lx.height > area[lx.i][lx.j + 1] && max_s < L[lx.i][lx.j + 1] + 1)
				max_s = L[lx.i][lx.j + 1] + 1;
		L[lx.i][lx.j] = max_s;
		if (result < max_s)
			result = max_s;
		qLx.pop();
	}
	cout << result << endl;
	return 0;
}