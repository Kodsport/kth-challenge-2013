#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define ALL(c) (c).begin(),(c).end()

typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<PII> VP;
typedef pair<VI,VP> board;
typedef set<board> H;

int n,m,k;
H seen;

bool dfs(const board& state) {
  if (seen.count(state)) return false;
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
	  if (dfs(state2)) return true;
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
	if (dfs(state2)) return true;
      }
      if (!state.second[0].first) {
	board state2(state);
	state2.second[0]=PII(v,1);
	state2.second[j].first=(--state2.second[j].second?v+1:0);
	sort(ALL(state2.second));
	if (dfs(state2)) return true;
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
