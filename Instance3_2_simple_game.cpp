#include <iostream>
#include <cstring>
using namespace std;

const int MAXIN = 75;
char board[MAXIN + 2][MAXIN + 2];
bool mark[MAXIN + 2][MAXIN + 2];
int minstep, w, h, to[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };

void search(int now_w, int now_h, int end_w, int end_h, int step, int f) {
	if (step > minstep)return;	//当前路径数大于minstep， 返回
	if (now_h == end_h&&now_w == end_w) {	//到达终点
		minstep = step;		//更新最小路径数
		return;
	}
	for (int i = 0; i < 4; i++) {	//枚举下一步的方向
		int next_w = now_w + to[i][0];	//更新位置
		int next_h = now_h + to[i][1];

		//T1: (next_w, next_h)在边界之内
		bool T1 = (next_w) > -1 && (next_w < w + 2) && (next_h > -1) && (next_h < h + 2);
		//T2: 该位置没有游戏卡片并且未走过
		bool T2 = (board[next_h][next_w] == ' ') && (mark[next_h][next_w] == false);
		//T3: 已经到达终点
		bool T3 = (next_w == end_w) && (next_h == end_h) && (board[next_h][next_w] == 'X');
		//下一位置有效的条件T1 && (T2 || T3)
		if (T1 && (T2 || T3)) {
			mark[next_h][next_w] = true;	//更新位置有效，标记该位置
			if (f == i)
				//下一步方向与当前方向相同，递归step不变
				search(next_w, next_h, end_w, end_h, step, i);
			else
				//方向不同，step + 1
				search(next_w, next_h, end_w, end_h, step + 1, i);
			mark[next_h][next_w] = false;	//回溯
		}
	}
}

int main() {
	int boardNum = 0;
	while (cin >> w >> h) {
		if (w == 0 && h == 0) break;
		boardNum++;
		cout << "Board #" << boardNum << ":" << endl;	

		//输入Board
		for (int i = 1; i <= h; i++) {
			cin.get();
			for (int j = 1; j <= w; j++)
				board[i][j] = cin.get();
		}
		//给Board加边框
		for (int i = 0; i < w + 2; i++)
			board[0][i] = board[h + 1][i] = ' ';
		for (int j = 0; j < h + 2; j++)
			board[j][0] = board[j][w + 1] = ' ';

		int begin_h, begin_w, end_h, end_w, count = 0;
		while (cin >> begin_w >> begin_h >> end_w >> end_h) {
			cin.get();
			if (begin_h == 0 && begin_w == 0 && end_w == 0 && end_h == 0)break;
			count++;
			minstep = 100000;	//初始化minstep为一个很大的数
			memset(mark, false, sizeof(mark));

			//递归搜索
			search(begin_w, begin_h, end_w, end_h, 0, -1);

			//输出结果
			if (minstep < 100000)
				cout << "Pair " << count << ": " << minstep << " segments" << endl;
			else
				cout << "Pair " << count << ": " << "impossible" << endl;
		}
		cout << endl;
	}
	return 0;
}