#include <iostream>
using namespace std;

int main(){
	int n;
	int s, a, b;
	//bool mark
	cin >> n;
	while (n--){
		int count = 0;
		int set_a[10001] = {}, set_b[10001] = {};
		cin >> s;
		cin >> a;
		for (int i = 1; i <= a; i++)
			cin >> set_a[i];
		cin >> b;
		for (int i = 1; i <= b; i++)
			cin >> set_b[i];
		for (int i = 1; i <= a; i++){
			for (int j = 1; j <= b; j++){
				if (set_a[i] + set_b[j] == s)
					count++;
			}
		}
		cout << count << endl;
	}
	return 0;
}