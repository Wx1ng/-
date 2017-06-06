#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int R, C;
int area[101][101];
int L[101][101];

struct Lx {
	int r, c, height;
	bool operator < (const Lx& l) const { return height > l.height; }
	Lx(int rr = 0, int cc = 0, int h = 0) :r(rr), c(cc), height(h) {}
};
priority_queue<Lx> qLx;

int main() {
	int result = 0;
	cin >> R >> C;
	memset(L, 1, sizeof(int)*101*101);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			cin >> area[i][j];
			L[i][j] = 1;
			qLx.push(Lx(i, j, area[i][j]));
		}
	}
	Lx lx;
	while (!qLx.empty()) {
		lx = qLx.top();
		int max_s = L[lx.r][lx.c];
		if (lx.r > 0)	//ио
			if (lx.height > area[lx.r - 1][lx.c] && max_s < L[lx.r - 1][lx.c] + 1)
				max_s = L[lx.r - 1][lx.c] + 1;
		if (lx.r < R - 1)	//об
			if (lx.height > area[lx.r + 1][lx.c] && max_s < L[lx.r + 1][lx.c] + 1)
				max_s = L[lx.r + 1][lx.c] + 1;
		if (lx.c > 0)	//вС
			if (lx.height > area[lx.r][lx.c - 1] && max_s < L[lx.r][lx.c - 1] + 1)
				max_s = L[lx.r][lx.c - 1] + 1;
		if (lx.c < C - 1)	//ср
			if (lx.height > area[lx.r][lx.c + 1] && max_s < L[lx.r][lx.c + 1] + 1)
				max_s = L[lx.r][lx.c + 1] + 1;
		L[lx.r][lx.c] = max_s;
		if (result < max_s)
			result = max_s;
		qLx.pop();
	}
	cout << result << endl;
	return 0;
}