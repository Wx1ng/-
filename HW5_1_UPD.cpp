#include <iostream>
using namespace std;

long long F[251][251] = { 0 };		//F[n][k]记录给定n，当前回文子序列第一个数>=k时，所有的种类
long long F_k[251][251] = { 0 };	//F_k[n][k]记录给定n，当前回文子序列第一个数=k时，所有的种类

bool mark_F[251][251] = { false };
bool mark_Fk[251][251] = { false };

long long get_Fk(int n, int k);

long long get_F(int n, int k){
	if (mark_F[n][k]) return F[n][k];

	for (int i = k; i <= n; i++)
		F[n][k] += get_Fk(n, i);
	mark_F[n][k] = true;
	return F[n][k];
}

long long get_Fk(int n, int k){
	if (mark_Fk[n][k]) return F_k[n][k];

	if (k == n || n == 2 * k)
		F_k[n][k] = 1;
	else if (k <= n / 3)
		F_k[n][k] = get_F(n - 2 * k, k);
	else
		F_k[n][k] = 0;
	mark_Fk[n][k] = true;
	return F_k[n][k];
}

int main(){
	int N;
	while (cin >> N){
		if (N == 0) break;
		cout << N << ' ' << get_F(N, 1) << endl;
	}
}
