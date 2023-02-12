#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int L1, L2, N;
    cin >> L1 >> L2 >> N;
    vector<int> tubes(N);
    for (int i = 0; i < N; ++i)
	cin >> tubes[i];
    int best1 = -1, best2 = -1;
    int a,b;
    for (int i = 0; i < N; ++i) {
	for (int j = i+1; j < N; ++j) {
	    if (tubes[i]+tubes[j] <= L1 && tubes[i]+tubes[j] > best1) {
		best1 = tubes[i]+tubes[j];
		a = i; b = j;
	    }
	}
    }
    for (int i = 0; i < N; ++i) {
	if (i == a || i == b)
	    continue;
	for (int j = i+1; j < N; ++j) {
	    if (j == a || j == b)
		continue;
	    if (tubes[i]+tubes[j] <= L2 && tubes[i]+tubes[j] > best2) {
		best2 = tubes[i]+tubes[j];
	    }
	}
    }

    if (best1 > -1 && best2 > -1)
	cout << best1 + best2 << endl;
    else
	cout << "Impossible" << endl;
}
