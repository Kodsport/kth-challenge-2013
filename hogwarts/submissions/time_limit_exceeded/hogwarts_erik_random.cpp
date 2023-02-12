/* This is an example solution to the "Hogwarts" problem from KTH Challenge 2013, held on April 21,
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
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>
#define rep(i,a,b) for(int i=a;i<b;++i)
#define MP(x,y) make_pair(x,y)
#define FI(x) (x).first
#define SE(x) (x).second
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef unsigned int unt;

int n, n_e, tower;
vvi adj;
vi seq;
bool inv;

void print() {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j)
			cout << adj[i][j] << ' ';
		cout << endl;
	}
}

void shift(int k, bool sign = true) {
//	cout << k << char(sign?'+':'-') << endl;
	if(sign) seq.pb(k); else seq.pb(-1-k);
	sign = !sign;
	vi row(adj[k]);	
	int last = k;
	bool around = false;
	int kp = sign?((k+1)%n):((k+n-1)%n);
  for(int l=kp; !(l==kp&&around); l=(sign?((l+1)%n):((l+n-1)%n)) ) {
		around=true;
		row[last]=row[l];
		last=l;
	}
	row[k] = false;
	rep(l,0,n) adj[k][l] = adj[l][k] = row[l];
}

void R_(istream& is) {
	adj.assign(n, vi(n, 0));
	for(int t = 0; t < n_e; ++t) {
		int x,y;
		is >> x >> y;
		adj[x][y] = adj[y][x] = true;
	}
}

unt r_a = 1664525;
unt r_c = 1013904223;
unt r_X = 31556926;

unt Rand() {
	return (r_X = r_a * r_X + r_c)>>8;
}

void panic() {
	vvi bdj;
	R_(cin);
	bdj = adj;
	R_(cin);	
	swap(adj, bdj);
	while(adj != bdj) {
		shift(Rand()%n, Rand()%2);
	}
	cout << seq.size() << endl;
	rep(i,0,seq.size()) {
		int t = seq[i];
		if(t >= 0) cout << "R " << ( t) << endl;
		else cout << "G " << ( -1-t) << endl;
	}
}

// R == +
// G == -

int main(int argc, char **argv) {
	cin >> n >> n_e;
	// Just panic.
	panic();
	return 0;
}
