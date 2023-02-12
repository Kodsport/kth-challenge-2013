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
//Solution by lukasP (Lukáš Poláček)
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef vector<int> vi;
typedef pair<int, int> pii;
const int INF = -123456789;
void improvMax(int &a, int b)
{
    a = max(a, b);
}
int main()
{
    int n, t; scanf("%d %d", &n, &t);

    vector<pii> people(n);
    rep(i,0,n)
    {
        int c, s;
        scanf("%d %d", &c, &s);
        people.push_back(pii(s, c));
    }

    sort(people.begin(), people.end());
    reverse(people.begin(), people.end());

    multiset<int> avail;
    int res = 0, u = 0;

    for (int i = t - 1; i >= 0; --i)
    {
        while (u < n && people[u].first == i)
        {
            avail.insert(-people[u].second);
            u++;
        }

        if (!avail.empty())
        {
            res += -*avail.begin();
            avail.erase(avail.begin());
        }
    }
    printf("%d\n", res);
}
