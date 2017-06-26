#include <iostream>
#include <cstring>
#include <bitset>
#include <math.h>
#include <queue>
using namespace std;

int ans = 0;
int board[16];
bitset<65550> status;
struct Node{
	int num;
	int count;
	Node(int n, int c) :num(n), count(c){}
	Node(){}
};
queue<Node> myQueue;

int statusNum(int* b){
	int Num = 0;
	for (int i = 0; i < 16; i++){
		if (b[i])
			Num += (1 << (15 - i));
	}
	return Num;
}

bool isEnd(int num){
	if (num == 0x0 || num == 0xffff)
		return true;
	return false;
}

bool BFS(){
	int num;
	status.reset();
	int No = statusNum(board);
	status.set(No, true);
	myQueue.push(Node(No, ans));
	while (!myQueue.empty()){
		Node tmp = myQueue.front();
		if (isEnd(tmp.num)) {
			ans = tmp.count;
			return true;
		}
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				Node t = tmp;
				int pos = i * 4 + j;
				t.num ^= 1 << (15 - pos);
				if (i - 1 >= 0)
					t.num ^= 1 << (15 - pos + 4);
				if (i + 1 < 4)
					t.num ^= 1 << (15 - pos - 4);
				if (j - 1 >= 0)
					t.num ^= 1 << (15 - pos + 1);
				if (j + 1 < 4)
					t.num ^= 1 << (15 - pos - 1);
				if (status[t.num]) continue;
				status.set(t.num, true);
				myQueue.push(Node(t.num, t.count+1));
			}
		}
		myQueue.pop();
	}
	return false;
}

int main(){
	memset(board, 0, sizeof(board));
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			char c = cin.get();
			if (c == 'b')
				board[i * 4 + j] = 1;
		}	
		cin.get();
	}

	if (BFS())
		cout << ans << endl;
	else
		cout << "Impossible" << endl;
	
	return 0;
}