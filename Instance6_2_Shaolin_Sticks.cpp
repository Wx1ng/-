#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int N, L;
vector<int> anLength;
int anUsed[65];
int nLastStickNo;
int DFS(int R, int M);

int main(){
	while (true){
		cin >> N;
		if (N == 0) break;

		int nTotalLen = 0;
		anLength.clear();
		for (int i = 0; i < N; i++){
			int n;
			cin >> n;
			anLength.push_back(n);
			nTotalLen += anLength[i];
		}
		sort(anLength.begin(), anLength.end(), isgreater<int, int>);

		for (L = anLength[0]; L <= nTotalLen / 2; L++){
			if (nTotalLen % L) continue;
			memset(anUsed, 0, sizeof(anUsed));
			if (DFS(N, L)){
				cout << L << endl;
				break;
			}
		}
		if (L > nTotalLen / 2)
			cout << nTotalLen << endl;
	}
	return 0;
}

int DFS_without_pruning(int R, int M){
	//M表示当前正在拼的棍子和L比还缺的长度
	if (R == 0 && M == 0) return true;
	if (M == 0)	//一根棍子刚拼完
		M = L;	//开始拼新的一根
	for (int i = 0; i < N; i++){
		if (!anUsed[i] && anLength[i] <= M){
			anUsed[i] = 1;
			if (DFS_without_pruning(R - 1, M - anLength[i])) return true;
			else anUsed[i] = 0;
		}
	}
	return false;
}

int DFS(int R, int M){	//附带剪枝方案的深度优先搜索
	/*****************************************
	1. 不在同一位置多次尝试长度相同的木棒
	2. 如果在不替换第一根木棒的情况下，无法拼出当前长度L的棍子，则推翻本次假设的棍子L长度，尝试下一个长度L
	3. 不要希望通过仅仅替换已拼好的棍子的最后一根解决失败的局面
	4. 确保已经拼好的部分长度是从长到短排列的
	********************************************/
	if (R == 0 && M == 0) return true;
	if (M == 0) M = L;
	int nStartNo = 0;	//当前使用的木棒No
	if (M != L)		//剪枝4
		nStartNo = nLastStickNo + 1;
	for (int i = nStartNo; i < N; i++){
		if (!anUsed[i] && anLength[i] <= M){
			if (i > 0){		//剪枝1
				if (anUsed[i - 1] == false && anLength[i] == anLength[i - 1])
					continue;
			}
			anUsed[i] = true;
			nLastStickNo = i;

			if (DFS(R - 1, M - anLength[i]))
				return true;
			else{
				anUsed[i] = false;	//说明本次不能使用第i根木棒
				if (anLength[i] == M || M == L)
					return false;	//剪枝3,2
			}
		}
	}
	return false;
}