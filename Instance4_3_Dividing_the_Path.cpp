#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 1 << 31;
const int MAX_L = 1000010;
const int MAX_N = 1010;
int F[MAX_L];	//F[L]就是答案
int cowThere[MAX_L];	//cowThere[i]为1表示点i有奶牛
int N, L, A, B;
struct Fx {
	int x, f;
	bool operator<(const Fx& a)const { return f > a.f; }		//优先队列默认为大顶堆，即队头元素为最大值
	Fx(int xx = 0, int ff = 0) :x(xx), f(ff) {}
};	//优先队列中，f值越小的越优先
priority_queue<Fx> qFx;

int main() {
	cin >> N >> L;
	cin >> A >> B;
	A <<= 1; B <<= 1;	//左移一位，相当于*2，变为覆盖直径
	memset(cowThere, 0, sizeof(cowThere));
	for (int i = 0; i < N; i++) {
		int s, e;
		cin >> s >> e;
		cowThere[s + 1]++;	//从s+1起进入一个奶牛区
		cowThere[e]--;	//从e起退出一个奶牛区
	}
	int inCows = 0;		//表示当前点位于多少头奶牛的活动范围之内
	for (int i = 0; i <= L; i++) {
		F[i] = INF;
		inCows += cowThere[i];
		cowThere[i] = inCows > 0;	//算出每个点是否有奶牛
	}
	for (int i = A; i <= B; i += 2) {	//初始化队列
		if (!cowThere[i]) {
			F[i] = 1;
			if (i < B + 2 - A)
				//求解F[i]时，要保证队列里的点x <= i - A
				//当x > i - A新增洒水的右边界会超出L
				qFx.push(Fx(i, 1));
		}
	}

	for (int i = B + 2; i <= L; i += 2) {
		if (!cowThere[i]) {
			Fx fx;
			while (!qFx.empty()) {
				fx = qFx.top();
				if (fx.x < i - B)
					qFx.pop();
				else
					break;
			}
			if (!qFx.empty())
				F[i] = fx.f + 1;
		}
		if (F[i + 2 - A] != INF)	//队列新增一个加一个喷水头可以抵达下个点的点
			qFx.push(Fx(i + 2 - A, F[i + 2 - A]));
	}

	if (F[L] == INF)
		cout << -1 << endl;
	else
		cout << F[L] << endl;
	return 0;
}
