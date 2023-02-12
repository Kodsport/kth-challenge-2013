/* Sample solution to Hogwarts from KTH Challenge 2013
 *
 * Solve time: about 2.5 hours with several external interruptions.
 * About 1-1.5 hours actual time I think.
 */
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;
typedef vector<int> vi;

bool debug = false;
#define dprintf debug && printf

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

void dump() {
	if (debug) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j)
				printf("%d", A[i][j]);
			printf("   ");
			for (int j = 0; j < N; ++j)
				printf("%d", B[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

// At most N/2 moves
void move(int i, int jsrc, int jdst) {
	dprintf("move %d %d %d\n", i, jsrc, jdst);
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
	//	dump();
}

// At most 2*N moves
void easyfix(int i1, int j1, int i2, int j2) {
	dprintf("easy fix %d %d %d %d\n", i1, j2, i2, j2);
	if (i2 == i1+1) swap(i2, j2);
	move(i2, j2, i1+1);
	move(i1, j1, i1+1);
	move(i1+1, i2, i1);
	move(i1, i1+1, j1);
}

// At most 2N + 2 moves
void messyfix(int i, int j1, int j2) {
	dprintf("messy fix %d %d %d\n", i, j1, j2);
	bool flipped = false;
	int k;
	if (A[i-1][j1] == A[i][j1]) {
		flipped = true;
		move(i, j2, j1);
		swap(j1, j2);
	}
	red(j1);
	move(i, j2, j1);
	green(j1);
	move(i, j1, j2);
	if (flipped) {
		swap(j1, j2);
		move(i, j1, j2);
	}
}

void fix(int i, int j) {
	dprintf("Fix %d %d\n", i, j);
	dump();
	for (int ii = i+1; ii < N; ++ii)
		for (int jj = 0; jj < N; ++jj)
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
	assert(0);
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
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			assert(A[i][j] == B[i][j]);
	dump();
	printf("%d\n", ops.size());
	for (auto s : ops) printf("%c %d\n", s < 0 ? 'G' : 'R', s < 0 ? -(s-1) : (s-1));
}
