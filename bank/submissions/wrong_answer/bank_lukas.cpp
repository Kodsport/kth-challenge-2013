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
#include <functional>
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef vector<int> vi;
const int INF = -123456789;
void improvMax(int &a, int b)
{
    a = max(a, b);
}
int main()
{
    int n, t; scanf("%d %d", &n, &t);

    vector<vi> people(t);
    rep(i,0,n)
    {
        int c, s;
        scanf("%d %d", &c, &s);
        people[s].push_back(c);
    }

    rep(i,0,t)
        sort(people[i].begin(), people[i].end(), greater<int>());

    int best[t + 1][t];
    rep(i,0,t+1) rep(j,0,t)
        best[i][j] = INF;
    best[t][0] = 0;

    for (int i = t - 1; i > 0; --i)
        for (int j = 0; j < t; j++) if (best[i][j] != INF)
        {
            int sum = 0;
            rep(k,0,people[i - 1].size())
            {
                if (j + (int)k >= t) break;
                sum += people[i - 1][k];
                improvMax(best[i - 1][j + k], best[i][j] + sum);
            }
            improvMax(best[i - 1][max(j - 1, 0)], best[i][j]);
        }

    printf("%d\n", best[0][0]);
}
