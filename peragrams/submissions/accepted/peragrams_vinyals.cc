/* This is an example solution to the "Peragrams" problem from KTH Challenge 2013, held on April 21,
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
#include <string>
using namespace std;

typedef vector<int> VI;

int main() {
  string s;
  cin >> s;
  VI seen(256);
  for (auto c:s) seen[c]++;
  int odd=-1;
  for (auto x:seen) if (x&1) ++odd;
  cout << max(odd,0) << endl;
}
