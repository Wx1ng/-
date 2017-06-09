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
	//M��ʾ��ǰ����ƴ�Ĺ��Ӻ�L�Ȼ�ȱ�ĳ���
	if (R == 0 && M == 0) return true;
	if (M == 0)	//һ�����Ӹ�ƴ��
		M = L;	//��ʼƴ�µ�һ��
	for (int i = 0; i < N; i++){
		if (!anUsed[i] && anLength[i] <= M){
			anUsed[i] = 1;
			if (DFS_without_pruning(R - 1, M - anLength[i])) return true;
			else anUsed[i] = 0;
		}
	}
	return false;
}

int DFS(int R, int M){	//������֦�����������������
	/*****************************************
	1. ����ͬһλ�ö�γ��Գ�����ͬ��ľ��
	2. ����ڲ��滻��һ��ľ��������£��޷�ƴ����ǰ����L�Ĺ��ӣ����Ʒ����μ���Ĺ���L���ȣ�������һ������L
	3. ��Ҫϣ��ͨ�������滻��ƴ�õĹ��ӵ����һ�����ʧ�ܵľ���
	4. ȷ���Ѿ�ƴ�õĲ��ֳ����Ǵӳ��������е�
	********************************************/
	if (R == 0 && M == 0) return true;
	if (M == 0) M = L;
	int nStartNo = 0;	//��ǰʹ�õ�ľ��No
	if (M != L)		//��֦4
		nStartNo = nLastStickNo + 1;
	for (int i = nStartNo; i < N; i++){
		if (!anUsed[i] && anLength[i] <= M){
			if (i > 0){		//��֦1
				if (anUsed[i - 1] == false && anLength[i] == anLength[i - 1])
					continue;
			}
			anUsed[i] = true;
			nLastStickNo = i;

			if (DFS(R - 1, M - anLength[i]))
				return true;
			else{
				anUsed[i] = false;	//˵�����β���ʹ�õ�i��ľ��
				if (anLength[i] == M || M == L)
					return false;	//��֦3,2
			}
		}
	}
	return false;
}