#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 1 << 31;
const int MAX_L = 1000010;
const int MAX_N = 1010;
int F[MAX_L];	//F[L]���Ǵ�
int cowThere[MAX_L];	//cowThere[i]Ϊ1��ʾ��i����ţ
int N, L, A, B;
struct Fx {
	int x, f;
	bool operator<(const Fx& a)const { return f > a.f; }		//���ȶ���Ĭ��Ϊ�󶥶ѣ�����ͷԪ��Ϊ���ֵ
	Fx(int xx = 0, int ff = 0) :x(xx), f(ff) {}
};	//���ȶ����У�fֵԽС��Խ����
priority_queue<Fx> qFx;

int main() {
	cin >> N >> L;
	cin >> A >> B;
	A <<= 1; B <<= 1;	//����һλ���൱��*2����Ϊ����ֱ��
	memset(cowThere, 0, sizeof(cowThere));
	for (int i = 0; i < N; i++) {
		int s, e;
		cin >> s >> e;
		cowThere[s + 1]++;	//��s+1�����һ����ţ��
		cowThere[e]--;	//��e���˳�һ����ţ��
	}
	int inCows = 0;		//��ʾ��ǰ��λ�ڶ���ͷ��ţ�Ļ��Χ֮��
	for (int i = 0; i <= L; i++) {
		F[i] = INF;
		inCows += cowThere[i];
		cowThere[i] = inCows > 0;	//���ÿ�����Ƿ�����ţ
	}
	for (int i = A; i <= B; i += 2) {	//��ʼ������
		if (!cowThere[i]) {
			F[i] = 1;
			if (i < B + 2 - A)
				//���F[i]ʱ��Ҫ��֤������ĵ�x <= i - A
				//��x > i - A������ˮ���ұ߽�ᳬ��L
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
		if (F[i + 2 - A] != INF)	//��������һ����һ����ˮͷ���Եִ��¸���ĵ�
			qFx.push(Fx(i + 2 - A, F[i + 2 - A]));
	}

	if (F[L] == INF)
		cout << -1 << endl;
	else
		cout << F[L] << endl;
	return 0;
}
