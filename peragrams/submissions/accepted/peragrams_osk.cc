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
//Solution by Oskar Werkelin Ahlin
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int cnt[26];
int main() {
    string str;
    cin >> str;
    for (auto it = str.begin(); it != str.end(); ++it) cnt[(*it)-'a']++;
    int ans = 0;
    for (int i = 0; i < 26; ++i) ans += cnt[i]&1;
    cout << max(0,ans-1) << endl;
}
