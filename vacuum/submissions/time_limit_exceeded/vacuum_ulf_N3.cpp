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
    sort(tubes.begin(),tubes.end());
    int best = -1;
    for (int i = 0; i < N; ++i) {
	for (int j = i+1; j < N; ++j) {
	    if (tubes[i]+tubes[j] <= L1) {
		int a = N-1;
		for (int k = 0; k < N; ++k) {
		    if (k == i || k == j) continue;
		    while (a >= 0 && (tubes[k]+tubes[a] > L2
				|| a==k || a==i || a==j)) --a;
		    if (a < 0) break;
		    best = max(best,tubes[i]+tubes[j]+tubes[k]+tubes[a]);
		}
	    }
	}
    }

    if (best > -1)
	cout << best << endl;
    else
	cout << "Impossible" << endl;
}
