#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
	int n = 1;	//记录当前Case的值
	int h = 0;	//文件当前所属层级
	vector<string> files_in;	//输入序列储存
	stack<string> files;
	string str;

	while (cin >> str){
		files_in.push_back(str);
		if (str == "#") break;
	}

	for (int i = 0; i < files_in.size(); i++){
		if (i == 0){
			cout << "DATA SET " << n << ":" << endl;
			cout << "ROOT" << endl;
		}
		files.push(files_in[i]);
		if (files_in[i][0] == 'd'){
			h++;
			for (int j = h; j > 0; j--)
				cout << "|     ";
			cout << files_in[i] << endl;
		}
		if (files_in[i] == "]"){
			string f;
			vector<string> f_v;
			files.pop();
			while (!files.empty()){
				f = files.top();
				files.pop();
				if (f[0] == 'd') break;
				f_v.push_back(f);
			}
			sort(f_v.begin(), f_v.end(), less<string>());
			for (int k = 0; k < f_v.size(); k++){
				for (int j = h; j > 0; j--)
					cout << "|     ";
				cout << f_v[k] << endl;
			}
			h--;
			//f_v.swap(vector<string>());
		}
		if (files_in[i] == "*"){
			string f;
			vector<string> f_v;
			files.pop();
			while (!files.empty()){
				f = files.top();
				files.pop();
				f_v.push_back(f);
			}
			sort(f_v.begin(), f_v.end(), less<string>());
			for (int k = 0; k < f_v.size(); k++){
				for (int j = h; j > 0; j--)
					cout << '|' << "     ";
				cout << f_v[k] << endl;
			}
			//f_v.swap(vector<string>());
			n++;
			if (files_in[i + 1] != "#"){
				cout << endl << "DATA SET " << n << ":" << endl;
				cout << "ROOT" << endl;
			}
		}
	}
	return 0;
}