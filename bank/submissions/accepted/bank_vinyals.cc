/* This is an example solution to the "Bank Queue" problem from KTH Challenge 2013, held on April
 * 21, 2013.
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
#include <queue>
#include <set>
using namespace std;

typedef pair<int,int> PII;
typedef priority_queue<PII> Q;
typedef set<int> SI;

int main() {
  int N,T;
  cin >> N >> T;
  Q q;
  for (int i=0;i<N;++i) {
    int c,t;
    cin >> c >> t;
    q.push(PII(c,t));
  }
  SI s;
  for (int t=0;t<T;++t) s.insert(t);
  int ret=0;
  while(!q.empty() && !s.empty()) {
    int c=q.top().first;
    int tmax=q.top().second;
    q.pop();
    auto it=s.upper_bound(tmax);
    if (it==s.begin()) continue;
    --it;
    ret+=c;
    s.erase(it);
  }
  cout << ret << endl;
}
