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
#include <cstdio>
#include <cstring>
using namespace std;
const int S = 'z'-'a'+1;
char words[5002][102];
int first[5000][S];
int last[5000][S];
int cumsum[5000][S][102];

int main() {
    int N,M;
    scanf("%d%d",&N,&M);
    memset(first,-1,sizeof(first));
    memset(last,-1,sizeof(last));
    memset(cumsum,0,sizeof(cumsum));
    for (int i = 0; i < N; ++i) {
	scanf("%s",words[i]);
	int k = 0;
	for (; words[i][k]; ++k)
	    last[i][words[i][k]-'a'] = k;
	for (--k; k >= 0; --k)
	    first[i][words[i][k]-'a'] = k;
	for (int j = 0; j < S; ++j) {
	    for (int k = 0; words[i][k]; ++k) {
		cumsum[i][j][k+1] = cumsum[i][j][k] + (words[i][k]-'a'==j);
	    }
	}
    }

    char plate[5];
    for (int i = 0; i < M; ++i) {
	scanf("%s",plate);
	bool success = false;
	for (int j = 0; j < N; ++j) {
	    if (first[j][plate[0]-'A'] != -1 && last[j][plate[2]-'A'] != -1
		    && cumsum[j][plate[1]-'A'][first[j][plate[0]-'A']+1] <
		    cumsum[j][plate[1]-'A'][last[j][plate[2]-'A']]) {
		puts(words[j]);
		success = true;
		break;
	    }
	}
	if (!success)
	    puts("No valid word");
    }
}



