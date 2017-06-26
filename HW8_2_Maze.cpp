#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

int maze[5][5];
bool mark[5][5];
struct Node{
	int x, y;
	int father;
	Node(int xx, int yy, int f) :x(xx), y(yy), father(f){}
	Node(){}
};
Node path[25];
int qHead, qTail;
stack<Node> result;

void BFS(){
	qHead = 0; qTail = 1;
	path[qHead] = Node(0, 0, -1);
	mark[0][0] = 1;
	while (qHead != qTail){
		Node tmp = path[qHead];
		if (tmp.x == 4 && tmp.y == 4)
			return;
		if (tmp.x - 1 >= 0 && !maze[tmp.x-1][tmp.y]){
			if (!mark[tmp.x - 1][tmp.y]){
				path[qTail++] = Node(tmp.x - 1, tmp.y, qHead);
				mark[tmp.x - 1][tmp.y] = 1;
			}
		}
		if (tmp.x + 1 < 5 && !maze[tmp.x + 1][tmp.y]){
			if (!mark[tmp.x + 1][tmp.y]){
				path[qTail++] = Node(tmp.x + 1, tmp.y, qHead);
				mark[tmp.x + 1][tmp.y] = 1;
			}
		}
		if (tmp.y - 1 >= 0 && !maze[tmp.x][tmp.y - 1]){
			if (!mark[tmp.x][tmp.y - 1]){
				path[qTail++] = Node(tmp.x, tmp.y - 1, qHead);
				mark[tmp.x][tmp.y - 1] = 1;
			}
		}
		if (tmp.y + 1 < 5 && !maze[tmp.x][tmp.y + 1]){
			if (!mark[tmp.x][tmp.y + 1]){
				path[qTail++] = Node(tmp.x, tmp.y + 1, qHead);
				mark[tmp.x][tmp.y + 1] = 1;
			}
		}
		qHead++;
	}
	return;
}

int main(){
	memset(maze, 0, sizeof(maze));
	memset(mark, 0, sizeof(mark));
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++)
			cin >> maze[i][j];
	}
	//cout << maze[4][4] << " " << mark[4][4] << endl;
	BFS();
	Node tmp = path[qHead];
	do{
		result.push(tmp);
		tmp = path[tmp.father];
	} while (tmp.father != -1);
	cout << "(0, 0)" << endl;
	while (!result.empty()){
		tmp = result.top();
		cout << "(" << tmp.x << ", " << tmp.y << ")" << endl;
		result.pop();
	}
	return 0;
}