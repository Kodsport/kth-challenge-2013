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
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int,int> pii;
typedef pair<int,pii> pipii;

int main() {
    int L[2], N;
    cin >> L[0] >> L[1] >> N;
    vector<int> tubes(N);
    for (int i = 0; i < N; ++i)
	cin >> tubes[i];
    sort(tubes.begin(),tubes.end());
    vector<set<pipii> > pairs(2);
    for (int i = 0; i < 2; ++i) {
	set<pii> p;
	int a = N-1;
	for (int j = 0; j < N; ++j) {
	    while (a >= 0 && tubes[j]+tubes[a] > L[i]) --a;
	    if (a < 0) break;
	    for (int k = a; k >= 0 && k > a-4; --k) {
		if (k == j) continue;
		if (p.count(pii(k,j))) {
		    pairs[i].insert(pipii(tubes[j]+tubes[k],pii(j,k)));
		    if (pairs[i].size() > 7)
			pairs[i].erase(pairs[i].begin());
		    p.erase(pii(k,j));
		} else
		    p.insert(pii(j,k));
	    }
	}
    }
    int best = -1;
    for (set<pipii>::iterator it0 = pairs[0].begin(); it0 != pairs[0].end(); ++it0) {
	for (set<pipii>::iterator it1 = pairs[1].begin(); it1 != pairs[1].end(); ++it1) {
	    if (it0->second.first != it1->second.first &&
		    it0->second.first != it1->second.second &&
		    it0->second.second != it1->second.first &&
		    it0->second.second != it1->second.second)
	    best = max(best,it0->first+it1->first);
	}
    }
    if (best > -1)
	cout << best << endl;
    else
	cout << "Impossible" << endl;
}
