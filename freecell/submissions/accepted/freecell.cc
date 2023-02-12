/* This is an example solution to the "Free Cell" problem from KTH Challenge 2013, held on April 21,
 * 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Marc Vinyals
#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <stack>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(c) (c).begin(),(c).end()

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VP;
typedef pair<VI,VP> board;
typedef set<board> H;
typedef stack<board> SS;

int n,m,k;
H seen;

bool dfs(const board& state) {
  seen.clear();
  SS st;
  st.push(state);
  while(!st.empty()) {
    board state=st.top();st.pop();
  if (seen.count(state)) continue;
  /*  FOR (i,0,n) cerr << state.first[i] << ' ';
  FOR (i,0,m) cerr << '(' << state.second[i].first << ' ' << state.second[i].second << ") ";
  cerr << endl;*/
  seen.insert(state);
  FOR (i,0,m) if (state.second[i].first==k) return true;
  FOR (i,0,n) {
    int v=state.first[i];
    if (v) {
      FOR (j,0,m) {
	if (!state.second[j].first || state.second[j].first==v+1) {
	  board state2(state);
	  state2.first[i]=0;
	  state2.second[j].first=v;
	  state2.second[j].second++;
	  sort(ALL(state2.first));
	  sort(ALL(state2.second));
	  st.push(state2);
	}
      }
    }
  }
  FOR (j,0,m) {
    int v=state.second[j].first;
    if (v) {
      if (n && !state.first[0]) {
	board state2(state);
	state2.first[0]=v;
	state2.second[j].first=(--state2.second[j].second?v+1:0);
	sort(ALL(state2.first));
	sort(ALL(state2.second));
	st.push(state2);
      }
      if (!state.second[0].first) {
	board state2(state);
	state2.second[0]=PII(v,1);
	state2.second[j].first=(--state2.second[j].second?v+1:0);
	sort(ALL(state2.second));
	st.push(state2);
      }
    }
  }
  }
  return false;
}

int main() {
  while (cin >> n >> m >> k) {
    ++m;
    board init(VI(n,0),VP(m,PII(0,0)));
    init.second.back()=PII(1,k);
    cout << (dfs(init)?"yes":"no") << endl;
  }
}
