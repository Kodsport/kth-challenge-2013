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
#include <cstring>
#include <string>
using namespace std;

const int S = 'z'-'a'+1;

int main() {
    int N,M;
    cin >> N >> M;
    bool one[S];
    bool two[S][S];
    int three[S][S][S];
    vector<string> words(N);

    memset(three,-1,sizeof(three));
    for (int i = 0; i < N; ++i) {
	memset(one,0,sizeof(one));
	memset(two,0,sizeof(two));
	string word;
	cin >> word;
	for (int j = 0; j < word.size(); ++j) {
	    for (int k = 0; k < S; ++k) {
		for (int l = 0; l < S; ++l)
		    if (two[k][l] && three[k][l][word[j]-'a'] == -1)
			three[k][l][word[j]-'a'] = i;
		two[k][word[j]-'a'] |= one[k];
	    }
	    one[word[j]-'a'] = true;
	}
	words[i] = word;
    }

    for (int i = 0; i < M; ++i) {
	string plate;
	cin >> plate;
	int a = three[plate[0]-'A'][plate[1]-'A'][plate[2]-'A'];
	if (a == -1)
	    cout << "No valid word" << endl;
	else
	    cout << words[a] << endl;
    }
}
