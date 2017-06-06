#include <iostream>
#include <cstring>
using namespace std;

const int MAXIN = 75;
char board[MAXIN + 2][MAXIN + 2];
bool mark[MAXIN + 2][MAXIN + 2];
int minstep, w, h, to[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

void search(int now_w, int now_h, int end_w, int end_h, int step, int f) {
	if (step > minstep)return;	//��ǰ·��������minstep�� ����
	if (now_h == end_h&&now_w == end_w) {	//�����յ�
		minstep = step;		//������С·����
		return;
	}
	for (int i = 0; i < 4; i++) {	//ö����һ���ķ���
		int next_w = now_w + to[i][0];	//����λ��
		int next_h = now_h + to[i][1];

		//T1: (next_w, next_h)�ڱ߽�֮��
		bool T1 = (next_w) > -1 && (next_w < w + 2) && (next_h > -1) && (next_h < h + 2);
		//T2: ��λ��û����Ϸ��Ƭ����δ�߹�
		bool T2 = (board[next_h][next_w] == ' ') && (mark[next_h][next_w] == false);
		//T3: �Ѿ������յ�
		bool T3 = (next_w == end_w) && (next_h == end_h) && (board[next_h][next_w] == 'X');
		//��һλ����Ч������T1 && (T2 || T3)
		if (T1 && (T2 || T3)) {
			mark[next_h][next_w] = true;	//����λ����Ч����Ǹ�λ��
			if (f == i)
				//��һ�������뵱ǰ������ͬ���ݹ�step����
				search(next_w, next_h, end_w, end_h, step, i);
			else
				//����ͬ��step + 1
				search(next_w, next_h, end_w, end_h, step + 1, i);
			mark[next_h][next_w] = false;	//����
		}
	}
}

int main() {
	int boardNum = 0;
	while (cin >> w >> h) {
		if (w == 0 && h == 0) break;
		boardNum++;
		cout << "Board #" << boardNum << ":" << endl;	

		//����Board
		for (int i = 1; i <= h; i++) {
			cin.get();
			for (int j = 1; j <= w; j++)
				board[i][j] = cin.get();
		}
		//��Board�ӱ߿�
		for (int i = 0; i < w + 2; i++)
			board[0][i] = board[h + 1][i] = ' ';
		for (int j = 0; j < h + 2; j++)
			board[j][0] = board[j][w + 1] = ' ';

		int begin_h, begin_w, end_h, end_w, count = 0;
		while (cin >> begin_w >> begin_h >> end_w >> end_h) {
			cin.get();
			if (begin_h == 0 && begin_w == 0 && end_w == 0 && end_h == 0)break;
			count++;
			minstep = 100000;	//��ʼ��minstepΪһ���ܴ����
			memset(mark, false, sizeof(mark));

			//�ݹ�����
			search(begin_w, begin_h, end_w, end_h, 0, -1);

			//������
			if (minstep < 100000)
				cout << "Pair " << count << ": " << minstep << " segments" << endl;
			else
				cout << "Pair " << count << ": " << "impossible" << endl;
		}
		cout << endl;
	}
	return 0;
}