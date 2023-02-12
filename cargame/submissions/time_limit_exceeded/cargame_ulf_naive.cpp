#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int N,M;
    cin >> N >> M;
    vector<string> words(N);
    for (int i = 0; i < N; ++i)
	cin >> words[i];
    for (int i = 0; i < M; ++i) {
	string plate;
	cin >> plate;
	for (int i = 0; i<3; ++i) plate[i] -= 'A'-'a';
	bool success = false;
	for (int j = 0; j < N; ++j) {
	    int a = 0;
	    for (int k = 0; a < 3 && k < words[j].length(); ++k)
		a += plate[a]==words[j][k];
	    if (a==3) {
		success = true;
		cout << words[j] << endl;
		break;
	    }
	}
	if (!success)
	    cout << "No valid word" << endl;
    }
}



