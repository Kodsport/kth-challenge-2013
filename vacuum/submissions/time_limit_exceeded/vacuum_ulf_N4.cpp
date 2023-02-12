#include <iostream>
#include <vector>
using namespace std;

int main() {
    int L1, L2, N;
    cin >> L1 >> L2 >> N;
    vector<int> tubes(N);
    for (int i = 0; i < N; ++i)
	cin >> tubes[i];
    int best = -1;
    for (int i = 0; i < N; ++i)
	for (int j = i+1; j < N; ++j)
	    if (tubes[i]+tubes[j] <= L1)
		for (int k = 0; k < N; ++k)
		    if (k != i && k != j)
			for (int l = k+1; l < N; ++l)
			    if (l != i && l != j && tubes[k]+tubes[l] <= L2)
				best = max(best,tubes[i]+tubes[j]+tubes[k]+tubes[l]);

    if (best > -1)
	cout << best << endl;
    else
	cout << "Impossible" << endl;
}
