#include <iostream>
using namespace std;

int board[30] = { 0 };
bool mark[30] = { false };

int find(int n){
	if (mark[n])return board[n];
	mark[n] = true;
	if (n % 2 == 1){
		board[n] = 0;
		return 0;
	}
	if (n == 0){
		board[n] = 1;
		return 1;
	}
	if (n == 2){
		board[n] = 3;
		return 3;
	}
	board[n] = find(n - 2) * find(2);
	for (int i = n - 4; i >= 0; i = i - 2)
		board[n] += find(i) * 2;
	return board[n];
}

int main(){
	int n;
	while (cin >> n){
		if (n == -1)break;
		cout << find(n) << endl;
	}
	return 0;
}