/* This is an example solution to the "Chicken Joggers" problem from KTH Challenge 2013, held on
 * April 21, 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Oskar Werkelin Ahlin
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_NODES 50005

using namespace std;

typedef pair<int,int> pii;

int N, L, S;
bool has[MAX_NODES];
bool added[MAX_NODES];
vector<pii> neigh[MAX_NODES];
vector<int> tree[MAX_NODES];
int memo[MAX_NODES][2];

void dfs(int cur, int from, int sum) {
    if (2*sum >= S) {
        return;
    }
    for (int i = 0; i < neigh[cur].size(); ++i) {
        pii next = neigh[cur][i];
        if (next.first == from) continue;
        tree[cur].push_back(next.first);
        dfs(next.first,cur,sum+next.second);
    }
}

int mvc(int cur, int prev) {
    int place = 1, dont_place = 0, already_placed = 0;

    if (memo[cur][prev] != -1) return memo[cur][prev];

    // place here
    for (int i = 0; i < tree[cur].size(); ++i) {
        int next = tree[cur][i];
        place += mvc(next,1);
    }
    
    // don't place here
    if (prev) { // we can't skip if we didn't place before
        for (int i = 0; i < tree[cur].size(); ++i) {
            int next = tree[cur][i];
            dont_place += mvc(next,0);
        }
    }

    // already has lamp
    if (has[cur]) {
        for (int i = 0; i < tree[cur].size(); ++i) {
            int next = tree[cur][i];
            already_placed += mvc(next,1);
        }
    }
    
    int ret = place;
    if (prev) ret = min(ret,dont_place);
    if (has[cur]) ret = min(ret,already_placed);
    return memo[cur][prev] = ret;
}

int main() {
    cin >> N >> S;
    for (int i = 0; i < N - 1; ++i) {
        int a,b,d;
        cin >> a >> b >> d;
        neigh[a].push_back(make_pair(b,d));
        neigh[b].push_back(make_pair(a,d));
    }
    cin >> L;
    for (int i = 0; i < L; ++i) {
        int cur;
        cin >> cur;
        has[cur] = true;
    }

    memset(memo,-1,sizeof(memo));
    added[1] = true;
    dfs(1,-1,0);

    cout << min(mvc(1,1),mvc(1,0)) << endl;
}
