/* This is an example solution to the "Cargame" problem from KTH Challenge 2013, held on April 21,
 * 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Erik Aas
#include <string.h>
#include <stdio.h>

int high[5000+10][26+10][26+10];
int low[5000+10][26+10][26+10];
//                ^approximation
int N, M;
char dict[10000+10][128];

/* 
	low[t][c][d] for int t, chars c and d, is
	the smallest k such that dictionary[t] has a 'd'
	at position k and a 'c' at some earlier point

	high[t][d][e] is analogous: largest k such that there's
	a 'd' at k and a 'e' at some later point

	CDE occurs in dict[t] iff low[t][c][d] <= high[t][d][e]
*/

int MIN(int x, int y) {
	if(x < y) return x;
	else return y;
}

int main() {
	scanf("%d%d", &N, &M);
	int t,i,j,q;
	char c,d,e;
	for(t = 0; t < N; ++t) {
		scanf("%s", dict[t]);
		int L = strlen(dict[t]);
		for(c=0;c <='z'-'a';++c)for(d=0;d<='z'-'a';++d) high[t][c][d] = low[t][c][d] = -1;
		for(i = 0; i < L; ++i) for(j = i+1; j < L; ++j) {
			c = dict[t][i];
			d = dict[t][j];
			c -= 'a'; d -= 'a';
			if(low[t][c][d] == -1) low[t][c][d] = j;
			else low[t][c][d] = MIN(low[t][c][d], j);
			high[t][c][d] = i;
		}
	}
	for(q = 0; q < M; ++q) {
		char p[3];
		scanf("%s", p);
		for(i = 0; i < 3; ++i)
			p[i] += 'x' - 'X';
		c = p[0] - 'a', d = p[1] - 'a', e = p[2] - 'a';
		int t = 0;
		while(t < N) {
			if(low[t][c][d] != -1 && high[t][d][e] != -1)
					if(low[t][c][d] <= high[t][d][e])
						break;
			++t;
		}
		if(t == N) printf("No valid word\n");
		else printf("%s\n", dict[t]);
	}

/* debug only 
	for(t = 0; t < N; ++t) {
		printf("%d : %s\n", t, dict[t]);
		for(c = 'a'; c <= 'z'; ++c) for(d = 'a'; d <= 'z'; ++d) {
			if( low[t][c-'a'][d-'a'] != -1) printf(" low[%c][%c] = %d\n", c,d,low[t][c-'a'][d-'a']);
			if(high[t][c-'a'][d-'a'] != -1) printf("high[%c][%c] = %d\n", c,d,high[t][c-'a'][d-'a']);
		}
	}
*/
}
