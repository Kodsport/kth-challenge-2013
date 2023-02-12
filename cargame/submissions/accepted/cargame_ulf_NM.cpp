/* This is an example solution to the "Car Game" problem from KTH Challenge 2013, held on April 21,
 * 2013.
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
#include <string>
using namespace std;

int main() {
    int N,M;
    cin >> N >> M;
    vector<string> words(N);
    vector<vector<int> > first(N);
    vector<vector<int> > last(N);
    vector<vector<vector<int> > > cumsum(N);
    for (int i = 0; i < N; ++i) {
	cin >> words[i];
	first[i] = vector<int>('z'-'a'+1,-1);
	last[i] = vector<int>('z'-'a'+1,-1);
	cumsum[i] = vector<vector<int> >('z'-'a'+1);
	for (int k = 0; k < words[i].length(); ++k)
	    last[i][words[i][k]-'a'] = k;
	for (int k = words[i].length()-1; k >= 0; --k)
	    first[i][words[i][k]-'a'] = k;
	for (int j = 0; j <= 'z'-'a'; ++j) {
	    cumsum[i][j] = vector<int>(words[i].length()+1,0);
	    for (int k = 0; k < words[i].length(); ++k) {
		cumsum[i][j][k+1] = cumsum[i][j][k] + (words[i][k]-'a'==j);
	    }
	}
	/*cout << "first " << first[i][0] << " last " << last[i][0] << endl;
	for (int k = 0; k < words[i].length()+1; ++k)
	    cout << cumsum[i][0][k] << " ";
	cout << endl;*/
    }

    for (int i = 0; i < M; ++i) {
	string plate;
	cin >> plate;
	bool success = false;
	for (int j = 0; j < N; ++j) {
	    if (first[j][plate[0]-'A'] != -1 && last[j][plate[2]-'A'] != -1
		    && cumsum[j][plate[1]-'A'][first[j][plate[0]-'A']+1] <
		    cumsum[j][plate[1]-'A'][last[j][plate[2]-'A']]) {
		cout << words[j] << endl;
		success = true;
		break;
	    }
	}
	if (!success)
	    cout << "No valid word" << endl;
    }
}



