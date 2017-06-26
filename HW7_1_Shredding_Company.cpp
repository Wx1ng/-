#include <iostream>
#include <math.h>
#include <vector>
#include <cstring>
using namespace std;

int target, number;
int numArray[6];
vector<int> outArray;
vector<int> resArray;
int sum, maxSum, minSum;
bool rejectFlag = 0;

void DFS(int numI, int nLeft) {
	if (nLeft == 0) {
		if (sum == maxSum) 
			rejectFlag = 1;
		if (sum > maxSum && sum <= target) {
			maxSum = sum;
			rejectFlag = 0;
			resArray.clear();
			resArray.assign(outArray.begin(), outArray.end());
		}
		return;
	}
	for (int i = 0; i < nLeft; i++) {
		int curNum = 0;
		for (int j = numI; j <= numI + i; j++)
			curNum = curNum * 10 + numArray[j];
		if (curNum > target) return;
		outArray.push_back(curNum);
		sum += curNum;
		if (sum > target) {
			sum -= curNum;
			outArray.pop_back();
			return;
		}
		DFS(numI + i + 1, nLeft - i - 1);
		sum -= curNum;
		outArray.pop_back();
	}
	return;
}

int main() {
	while (true) {
		cin >> target >> number;
		if (target == 0 && number == 0) break;
		sum = 0; minSum = 0; maxSum = 0; rejectFlag = 0;
		memset(numArray, 0, sizeof(numArray));
		int n = 0;
		for (int i = 0; i < 6; i++) {
			if (number / int(pow(10, 5 - i)) != 0) 
				break;
			//number = number % int(pow(10, 5 - i));
			n++;
		}
		for (int i = n; i < 6; i++) {
			numArray[i - n] = number / int(pow(10, 5 - i));
			number = number % int(pow(10, 5 - i));
			minSum += numArray[i - n];
		}

		if (minSum > target) {
			cout << "error" << endl;
			continue;
		}
		DFS(0, 6 - n);
		if (rejectFlag) {
			cout << "rejected" << endl;
			continue;
		}
		cout << maxSum << ' ';
		for (int i = 0; i < resArray.size() - 1; i++)
			cout << resArray[i] << ' ';
		cout << resArray[resArray.size() - 1] << endl;
	}
	return 0;
}