/* This is an example solution to the "Car Game" problem from KTH Challenge 2013, held on April
 * 21, 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Per Austrin
#include <cstdio>
#include <cstring>

char dict[5000][200];
int next[5000][101][27];
int N, M;

bool match(char *str, int i) {
	int at = 0;
	for (int j = 0; at != -1 && j < 3; ++j)
		at = next[i][at][str[j]-'A'];
	return at != -1;
}

char *search(char *str) {
	for (int i = 0; i < N; ++i)
		if (match(str, i)) return dict[i];
	return "No valid word";
}

int main(void) {
	char str[200];
	scanf("%d%d", &N, &M);
	memset(next, -1, sizeof(next));
	for (int i = 0; i < N; ++i) {
		scanf("%s", dict[i]);
		for (int j = strlen(dict[i])-1; j >= 0; --j) {
			memcpy(next[i][j], next[i][j+1], sizeof(int)*27);
			next[i][j][dict[i][j]-'a'] = j+1;
		}
	}
	for (int i = 0; i < M; ++i) {
		scanf("%s", str);
		printf("%s\n", search(str));
	}
	return 0;
}
