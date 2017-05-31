#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 1000000;
int t, n, x, y, maxHeight;
struct Platform{
	int Lx, Rx, h;
	bool operator < (const Platform & p2) const {
		return h > p2.h;
	}
};
Platform platforms[1001];
int leftMinTime[1001];
int rightMinTime[1001];

int MinTime(int l, bool isLeft){
	int height = platforms[l].h;
	int x;
	if (isLeft) x = platforms[l].Lx;
	else x = platforms[l].Rx;
	int i;
	for (i = l + 1; i <= n; i++){
		if (platforms[i].Lx <= x && platforms[i].Rx >= x)
			break;
	}
	if (i <= n){
		if (height - platforms[i].h > maxHeight)
			return INF;
	}
	else{
		if (height > maxHeight)
			return INF;
		else
			return height;
	}
	int nLeftTime = height - platforms[i].h + x - platforms[i].Lx;
	int nRightTime = height - platforms[i].h + platforms[i].Rx - x;
	if (leftMinTime[i] == -1)
		leftMinTime[i] = MinTime(i, true);
	if (rightMinTime[i] == -1)
		rightMinTime[i] = MinTime(i, false);
	nLeftTime += leftMinTime[i];
	nRightTime += rightMinTime[i];
	if (nLeftTime < nRightTime) 
		return nLeftTime;
	return nRightTime;
}

int main(){
	cin >> t;
	while (t--){
		memset(leftMinTime, -1, sizeof(leftMinTime));
		memset(rightMinTime, -1, sizeof(rightMinTime));
		cin >> n >> x >> y >> maxHeight;
		platforms[0].Lx = x;
		platforms[0].Rx = x;
		platforms[0].h = y;
		for (int j = 1; j <= n; j++)
			cin >> platforms[j].Lx >> platforms[j].Rx >> platforms[j].h;
		sort(platforms, platforms + n + 1);
		cout << MinTime(0, true) << endl;
	}
	return 0;
}