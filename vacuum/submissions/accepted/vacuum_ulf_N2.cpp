/* This is an example solution to the "Vacuum Tubes" problem from KTH Challenge 2013, held on April
 * 21, 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Ulf Lundström
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
    int best = -1, a = N-1;
    for (int i = 0; i < N; ++i) {
	while (a >= 0 && tubes[i]+tubes[a] > L1) --a;
	if (a < 0) break;
	for (int j = a; j > a-4 && j >= 0; --j) {
	    if (i == j) continue;
	    int b = N-1;
	    for (int k = 0; k < N; ++k) {
		if (k == i || k == j) continue;
		while (b >= 0 && (tubes[k]+tubes[b] > L2 
			    || b==i || b==j || b==k))
		   --b;
		if (b < 0) break;
		best = max(best,tubes[i]+tubes[j]+tubes[k]+tubes[b]);
	    }
	}
    }

    if (best > -1)
	cout << best << endl;
    else
	cout << "Impossible" << endl;
}
