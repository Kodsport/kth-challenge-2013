/* This is an example solution to the "Vacuum Tubes" problem from KTH Challenge 2013, held on April
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
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <queue>
#include <bitset>
#include <utility>
#include <list>
#include <numeric>

#include <cstdio>
#include <cmath>
#include <cctype>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main()
{
    int l[2], n;
    scanf("%d %d %d", &l[0], &l[1], &n);

    vi a(n);
    rep(i,0,n)
        scanf("%d", &a[i]);

    sort(a.begin(), a.end());

    int other[n+1][2];
    rep(k,0,2) rep(i,0,n)
    {
        int &u = other[i][k];
        if (i == 0)
            u = n - 1;
        else
            u = other[i - 1][k];

        while (u >= 0 && a[u] + a[i] > l[k])
            u--;
    }

    int res = -1;
    rep(i,0,n) if (other[i][0] > i)
        rep(j,0,n) if (other[j][1] > j && i != j)
            for (int k = other[i][0]; k >= other[i][0]-3 && k > i; k--) if (k != j)
                rep(v,other[j][1]-3,other[j][1]+1) if (v > j && k != v && i != v)
                    res = max(res, a[i] + a[k] + a[j] + a[v]);

    if (res == -1)
        printf("Impossible\n");
    else
        printf("%d\n", res);
}
