/* This is an example solution to the "Hogwarts" problem from KTH Challenge 2013, held on April 21,
 * 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 *
 * Solution by Per Austrin
 *
 * #moves can definitely be made much better with some more effort
 *
 * Solve time: about 3 hours with several external interruptions.
 * About 1-1.5 hours actual time I think.
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
typedef vector<int> vi;

int N;
int A[200][200], B[200][200];

vi ops;

void read(int M, int X[200][200]) {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			X[i][j] = i==j;
	for (int i = 0, a, b; i < M; ++i) {
		scanf("%d%d", &a, &b);
		X[a][b] = X[b][a] = 1;
	}
}

void doswap(int i, int j, int k) {
	j += j >= i;
	k += k >= i;
	swap(A[i][j], A[i][k]);
	swap(A[j][i], A[k][i]);
}

void red(int i) {
	ops.push_back(i+1);
	for (int j = N-2, k = 0; j > 0; k = j--) doswap(i, j, k);
}

void green(int i) {
	ops.push_back(-(i+1));
	for (int j = 0, k = N-2; j < N-2; k = j++) doswap(i, j, k);
}

// At most N/2 moves
void move(int i, int jsrc, int jdst) {
	if ((N+jdst-jsrc) % N < (N+jsrc-jdst) % N) {
		while (jsrc != jdst) {
			red(i);
			jsrc = (jsrc + 1) % N;
			if (jsrc == i) jsrc = (jsrc+1) % N;
		}
	} else {
		while (jsrc != jdst) {
			green(i);
			jsrc = (N + jsrc - 1) % N;
			if (jsrc == i) jsrc = (N + jsrc-1) % N;
		}
	}
}

// At most 2*N moves
void easyfix(int i1, int j1, int i2, int j2) {
	if (i2 == i1+1) { // not so easy any more...
		if (j2 == i1) {
			green(i1+1);
			j2 = (N+j2-1) % N;
		}
		swap(i2, j2);
	} else {
		move(i2, j2, i1+1);
	}
	move(i1, j1, i1+1);
	move(i1+1, i2, i1);
	move(i1, i1+1, j1);
}

// At most 2N + 2 moves
void messyfix(int i, int j1, int j2) {
	if (A[i][j1] == A[0][1]) {
		messyfix(i, j2, j1);
		return;
	}
	move(i, j1, 1);
	green(1);
	move(i, j2, j1);
	red(1);
	move(i, j1, j2);	
	move(i, 1, j1);
}

void fix(int i, int j) {
	for (int ii = i+1; ii < N; ++ii)
		for (int jj = 0; jj < ii; ++jj)
			if (A[ii][jj] == B[i][j]) {
				easyfix(i, j, ii, jj);
				return;
			}
	for (int jj = j+1; jj < i; ++jj) {
		if (A[i][jj] == B[i][j]) {
			messyfix(i, j, jj);
			return;
		}
	}
	// assert(0);
}


int main(void) {
	int M;
	scanf("%d%d", &N, &M);
	read(M, A);
	read(M, B);
	for (int i = 1; i < N; ++i)
		for (int j = 0; j < i; ++j)
			if (A[i][j] != B[i][j])
				fix(i, j);
	printf("%d\n", ops.size());
	for (auto s: ops) printf("%c %d\n", s < 0 ? 'G' : 'R', s < 0 ? -s-1 : s-1);
}
