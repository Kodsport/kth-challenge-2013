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
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>
#define rep(i,a,b) for(int i=a;i<b;++i)
#define repd(i,a,b) for(int i=b-1; i >= a; --i)
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;

int n, n_e, tower;
bool inv;
const bool RED = true,
					 GREEN = false;

vvi adj;
vi seq;
vvi A, B;

// debug only
void print() {
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j)
			cout << adj[i][j] << ' ';
		cout << endl;
	}
}

// if sign is true, press red button #k. Otherwise, press green button #k.
void shift(int k, bool sign = true) {
    int n = adj.size();
		if(sign) seq.pb(k); else seq.pb(-1-k);
    vi row(adj[k]);
    row.erase(row.begin() + k);
    if(sign == RED) 
			rotate(row.begin(), row.begin() + (n - 2), row.end());
    else // sign == GREEN 
			rotate(row.begin(), row.begin() + 1, row.end());

		rep(l,0,n-1) {
        int rl = l + (l >= k);
        adj[k][rl] = adj[rl][k] = row[l];
    }
}

// number of staircases connected to k
int deg(int k,int start = 0) {
	int rt = 0;
	rep(l,start,n)
		if(adj[k][l]) 
			++rt;
	return rt;
}

void read(istream& is, vvi&adj) {
	adj.assign(n, vi(n, 0));
	rep(t, 0, n_e) {
		int x,y;
		is >> x >> y;
		adj[x][y] = adj[y][x] = true;
	}
}

// are there staircases in each of {1, i}, {2, i}, ..., {i-1, i}?
bool filled(int i) {
	rep(j,0,tower) 
		if(i != j && !adj[i][j])
			return false;
		return true;
}

// Works with higher probability than all other functions
// in sight.
void panic() {
	vvi bdj;
	bdj = A;
	adj = B;
	swap(adj, bdj);
	while(adj != bdj) {
		shift(rand()%n, rand()%2);
	}
}

// transform adj to the lex-smallest graph with n nodes
vi compress() {
	seq.clear();
	if(inv) rep(i, 0, n) rep(j, 0, n) if(i != j) adj[i][j] = !adj[i][j];
	if(n_e == 0 || n_e == (n*(n-1))/2) return seq;

	tower = n - 1;
	int f = 0;

	//make sure all there are staircases f is filled() for
	// each f <= M where M is largest possible. Use the 
	// tower node to do this

	while(1) {
		if(deg(f) >= n - 2) while(!filled(f)) shift(f, RED);
		while(filled(f)) ++f;
		if(f == tower) break;
		while(adj[tower][f]) shift(f, RED);
		int k = tower;
		while(deg(k, f + 1) == 0) --k;
		if(k <= f) break;
		int ct = 0;
		while(deg(tower) == 0) shift(k, RED), ++ct;
		while(!adj[tower][f]) shift(tower, RED);
		while(ct--) shift(k, GREEN);
	}
	
	//make sure the staircases connected f are precisely {1, f}, ..., {k, f} 
	// for some k. That k will be < f.

	while(1) {
		int f_z = bool(f == 0);
		while(f_z < tower && adj[f][f_z]){ ++f_z; if(f_z == f) ++f_z;}
		if(f_z == tower) break;
		int f_o = f_z + 1;
		while(f_o < n && !adj[f][f_o]){ ++f_o; if(f_o == f) ++f_o;}
		if(f_o == n) break;
		if(f_o == tower) {
			shift(f, GREEN);
		} else {
			int l = f_z;
			int k = f_o;
			int ct = 0;
			while(k != tower) {
				shift(f, RED);
				++ct, ++k, ++l;
				if(k == f) ++k;
				if(l == f) ++l;
			}
			shift(tower);
			while(l != tower) {
				shift(f, RED);
				++ct, ++l;
				if(l == f) ++l;
			}
			shift(tower,GREEN);
			while(ct--)shift(f,GREEN);
		}
	}
	return seq;
}

int main(int argc, char **argv) {
	cin >> n >> n_e;
	read(cin, A);
	read(cin, B);
	vi ops;	
	if(n < 5) {
		// panic.
		panic();
		ops = seq;
	} 	else {

		// makes sure there are more non-edges than edges
		// does _not_ change n_e!
		inv = (2*n_e > (n*(n-1))/2);
		adj = A;
		vi AA = compress();
		adj = B;
		vi BB = compress();
		// from A to lex-smallest graph
		rep(i, 0, AA.size()) ops.push_back(AA[i]);
		// from lex-smallest graph to B
		repd(i, 0, BB.size()) ops.push_back(-1 - BB[i]);
	}
	cout << ops.size() << endl;
	adj = A;
	rep(i,0,ops.size()) {
		if(ops[i] >= 0) {
			cout << "R " << ops[i] << endl;
	//		shift(ops[i], RED);
		} else {
			cout << "G " <<(-1-ops[i]) << endl;
	//		shift(-1-ops[i], GREEN);
		}
	}
	
	// debug only
	/*
	rep(i,0,n)
		rep(j,0,n)
			assert(adj[i][j] == B[i][j]);
	*/
	return 0;
}
