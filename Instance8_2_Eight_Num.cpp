#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;

int goalStatus;		//Ŀ��״̬
bitset<362880> Flags;	//�ڵ��Ƿ���չ�ı��
const int MAXS = 400000;
char result[MAXS];	//���
struct Node{
	int status;		//״̬
	int father;		//���ڵ�ָ��
	char move;		//���ڵ㵽���ڵ���ƶ���ʽ u/d/r/l
	Node(int s, int f, char m) :status(s), father(f), move(m){}
	Node(){};
};
Node myQueue[MAXS];		//״̬���У�״̬����362880
int qHead; int qTail;	//��ͷ�Ͷ�βָ��
char sz4Moves[] = "udrl";	//���ֶ���
unsigned int factorial[21];	//���0-20�Ľ׳�

unsigned int getPermutationNumForInt(int* perInt, int len){
//perInt���������0��len-1��һ�����У������ǵڼ�������
//len������21
	unsigned int num = 0;
	bool used[21];
	memset(used, 0, sizeof(bool)*len);
	for (int i = 0; i < len; i++){
		unsigned int n = 0;
		for (int j = 0; j < perInt[i]; j++){
			if (!used[j])
				n++;
		}
		num += n*factorial[len - i - 1];
		used[perInt[i]] = true;
	}
	return num;
}

template <class T>
unsigned int getPermutatationNum(T s1, T s2, int len){
//�������У�����š�[s1, s1+len)������ŵ�0�����У�[s2, s2+len)��Ҫ����ŵ�����
//���߱���һ������len���ܳ���21
//���е�ÿ��Ԫ�ض���һ�����������еı��
	int perInt[21];		//Ҫת����[0, len-1]������������
	for (int i = 0; i < len; i++){
		for (int j = 0; j < len; j++){
			if (*(s2 + i) == *(s1 + j)){
				perInt[i] = j;
				break;
			}
		}  
	}
	unsigned int num = getPermutationNumForInt(perInt, len);
	return num;
}

template <class T>
void genPermutationByNum(T s1, T s2, int len, unsigned int No){
//�������б�ţ���������len���ܳ���21
//[s1, s1+len)������ŵ�0��permutation�����е�ÿ��Ԫ�ض���һ��
	int perInt[21];		//Ҫת����[0, len-1]������������
	bool used[21];
	memset(used, 0, sizeof(bool)*len);
	for (int i = 0; i < len; i++){
		unsigned int tmp;
		int n = 0; int j;
		for (j = 0; i < len; j++){
			if (!used[j]){
				if (factorial[len - i - 1] >= No + 1) break;
				else No -= factorial[len - i - 1];
			}
		}
		perInt[i] = j;
		used[j] = true;
	}
	for (int i = 0; i < len; i++)
		*(s2 + i) = *(s1 + perInt[i]);
}

int strStatusToIntStatus(const char* strStatus){
//�ַ�����ʽ����̬��ת��Ϊ������ʽ��״̬
	return getPermutatationNum("012345678", strStatus, 9);
}

void intStatusToStrStatus(int n, char* strStatus){
	genPermutationByNum((char*)"012345678", strStatus, 9, n);
}

int newStatus(int nStatus, char cMove){
//���nStatus����cMove�ƶ���õ�����״̬�����ƶ��������򷵻�-1
	char szTmp[20]; int nZeroPos;
	intStatusToStrStatus(nStatus, szTmp);
	for (int i = 0; i < 9; i++){
		if (szTmp[i] == '0'){
			nZeroPos = i;
			break;
		}
	}
	switch (cMove){
	case 'u':
		if (nZeroPos - 3 < 0) return -1;	//�ո��ڵ�һ��
		else{
			szTmp[nZeroPos] = szTmp[nZeroPos - 3];
			szTmp[nZeroPos - 3] = '0';
		}
		break;
	case 'd':
		if (nZeroPos + 3 > 8) return -1;
		else{
			szTmp[nZeroPos] = szTmp[nZeroPos + 3];
			szTmp[nZeroPos + 3] = '0';
		}
		break;
	case 'l':
		if (nZeroPos % 3 == 0) return -1;
		else{
			szTmp[nZeroPos] = szTmp[nZeroPos - 1];
			szTmp[nZeroPos - 1] = '0';
		}
		break;
	case 'r':
		if (nZeroPos % 3 == 2) return -1;
		else{
			szTmp[nZeroPos] = szTmp[nZeroPos + 1];
			szTmp[nZeroPos + 1] = '0';
		}
		break;
	default:
		break;
	}
	return strStatusToIntStatus(szTmp);
}

bool BFS(int nStatus){	//Ѱ�Ҵӳ�ʼ״̬nStatus��Ŀ���·��
	int nNewStatus;
	Flags.reset();	//���������չ���
	qHead = 0; qTail = 1;
	myQueue[qHead] = Node(nStatus, -1, 0);
	while (qHead != qTail){	//���в�Ϊ��
		nStatus = myQueue[qHead].status;
		if (nStatus == goalStatus)	//�ҵ�Ŀ��״̬
			return true;
		for (int i = 0; i < 4; i++){
			nNewStatus = newStatus(nStatus, sz4Moves[i]);
			if (nNewStatus == -1) continue;	//�����ƣ�����һ��
			if (Flags[nNewStatus])continue;	//��չ����Ѵ��ڣ������
			Flags.set(nNewStatus, true);	//��������չ���
			myQueue[qTail++] = Node(nNewStatus, qHead, sz4Moves[i]);	//�½ڵ����
		}
		qHead++;
	}
	return false;
}

int main(){
	factorial[0] = factorial[1] = 1;
	for (int i = 2; i < 21; i++)
		factorial[i] = i*factorial[i - 1];
	goalStatus = strStatusToIntStatus("123456780");
	char szLine[50]; char szLine2[20];
	while (cin.getline(szLine, 48)){
		int i, j;
		for (i = 0, j = 0; szLine[i]; i++){
			if (szLine[i] != ' '){
				if (szLine[i] == 'x')
					szLine2[j++] = '0';
				else
					szLine2[j++] = szLine[i];
			}
		}
		szLine2[j] = 0;	//�ַ�����ʽ�ĳ�ʼ״̬
		int sumGoal = 0;	//�Ӵ��Ժ�����ż���ж��Ƿ��н�
		for (int i = 0; i < 8; i++)
			sumGoal += i - 1;
		int sumOri = 0;
		for (int i = 0; i < 9; i++){
			if (szLine2[i] == '0')
				continue;
			for (int j = 0; j < i; j++){
				if (szLine2[j] < szLine2[i] && szLine2[j] != '0')
					sumOri++;
			}
		}
		if (sumOri % 2 != sumGoal % 2){
			cout << "unsolvable" << endl;
			continue;
		}
		if (BFS(strStatusToIntStatus(szLine2))){
			int nMoves = 0;
			int nPos = qHead;
			do{	//ͨ��father�ҵ��ɹ���״̬���С������Ӧ����
				result[nMoves++] = myQueue[nPos].move;
				nPos = myQueue[nPos].father;
			} while (nPos);	//nPos=0˵���Ѿ����˵���ʼ״̬��
			for (int i = nMoves - 1; i >= 0; i--)
				cout << result[i];
		}
		else
			cout << "unsolvable" << endl;
	}
}