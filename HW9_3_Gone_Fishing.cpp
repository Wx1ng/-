#include <iostream>
#include <cstring>
using namespace std;

int n, h;
int T[25], F[25], D[25];
int tFishing;	//用于钓鱼的时间
int tFishAvail[25];	//当前鱼塘剩余的鱼数
int tFishingTime[25][25];	//每个鱼塘钓鱼的时长
int totalNum[25];		//最大钓鱼量

int main() {
	while (cin >> n) {
		if (n == 0) break;
		cin >> h;
		memset(T, 0, sizeof(T));
		memset(F, 0, sizeof(F));
		memset(D, 0, sizeof(D));
		memset(tFishingTime, 0, sizeof(tFishingTime));
		for (int i = 0; i < n; i++)
			cin >> F[i];
		for (int i = 0; i < n; i++)
			cin >> D[i];
		for (int i = 1; i < n; i++)
			cin >> T[i];
		h = h * 12;

		for (int i = 0; i < n; i++) {
			totalNum[i] = 0;
			tFishing = h;	//用于钓鱼的时间
			//memset(tFishingTime[i], 0, sizeof(tFishingTime));
			for (int j = 0; j <= i; j++)
				tFishAvail[j] = F[j];
			for (int j = 1; j <= i; j++)
				tFishing -= T[j];
			int empty = 0;
			while (tFishing != 0 && empty <= i) {
				//int maxFish = 0;	//当前时间能钓最多的鱼
				int maxIndex = 0;	//能钓最多鱼的鱼塘
				for (int j = empty; j <= i; j++) {
					if (tFishAvail[maxIndex] < tFishAvail[j])
						maxIndex = j;
				}
				tFishingTime[i][maxIndex]++;
				totalNum[i] += tFishAvail[maxIndex];
				tFishAvail[maxIndex] -= D[maxIndex];
				tFishAvail[maxIndex] = tFishAvail[maxIndex] > 0 ? tFishAvail[maxIndex] : 0;
				tFishing--;
				for (int j = empty; j <= i; ++j){
					if (tFishAvail[j] == 0)	
						empty++;
					else 
						break;
				}
			}
			if (tFishing > 0)
				tFishingTime[i][0] += tFishing;
		}
		int index = 0;
		for (int i = 0; i < n; i++)
			if (totalNum[i] > totalNum[index])
				index = i;
		for (int x = 0; x < n - 1; x++)
			cout << tFishingTime[index][x] * 5 << ", ";
		cout << tFishingTime[index][n - 1] * 5 << endl;
		cout << "Number of fish expected: " << totalNum[index] << endl;
		cout << endl;
	}
	return 0;
}