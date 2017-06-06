#include <stdio.h>
using namespace std;

const static int inf = 0x7FFFFFFF;
//时钟旋转设定
//影响该位置的时钟
const int affect_clock[10][5] = { {}, { 1, 2, 4 }, { 1, 2, 3, 5 }, { 2, 3, 6 },
								{ 1, 4, 5, 7 }, { 1, 3, 5, 7, 9 }, { 3, 5, 6, 9 },
								{ 4, 7, 8 }, { 5, 7, 8, 9 }, { 6, 8, 9 } };

inline int getState(int clock[], int n, int rotate[]){
	int state = clock[n];
	for (int i = 0; i < 5; i++){
		state += rotate[affect_clock[n][i]];
	}
	return state;
}

int main(){
	int min_count = inf;
	int cur_count = 0;
	int clock[10] = { 0 };
	int rotate[10] = { 0 };
	int ans_rotate[10] = { 0 };
	for (int i = 1; i < 10; i++){
		scanf("%d", &clock[i]);
	}
	//当前三个时钟旋转次数确定时，所有的旋转都得到确定
	//对前三个时钟旋转次数进行枚举
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			for (int k = 0; k < 4; k++){
				rotate[1] = i;
				rotate[2] = j;
				rotate[3] = k;
				//计算时钟4-9的操作
				for (int c = 4; c < 10; c++){
					//由于位置5不受时钟8的影响，将其单独考虑
					if (c == 8)	continue;
					int state = getState(clock, c - 3, rotate);
					rotate[c] = (4 - state % 4) % 4;
				}
				//计算位置8旋转次数
				rotate[8] = (4 - getState(clock, 8, rotate) % 4) % 4;
				//计算时钟5、7、9的状态，如果不全部指向0点，跳过
				bool success = true;
				for (int c = 5; c < 10; c += 2){
					if (getState(clock, c, rotate) % 4 != 0){
						success = false;
						break;
					}
				}
				if (success){
					for (int cl = 1; cl < 10; cl++){
						cur_count += rotate[cl];
					}
					if (cur_count < min_count){
						min_count = cur_count;
						for (int cl = 1; cl < 10; cl++){
							ans_rotate[cl] = rotate[cl];
						}
					}
				}
				cur_count = 0;
				for (int cl = 1; cl < 10; cl++){
					rotate[cl] = 0;
				}
			}
		}
	}
	if (min_count == inf){
		printf("inf\n");
	}
	else{
		for (int i = 1; i < 10; i++){
			for (int time = 0; time < ans_rotate[i]; time++){
				printf("%d ", i);
			}
		}
		printf("\n");
	}
	return 0;
}