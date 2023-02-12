/* This is an example solution to the "Car Game" problem from KTH Challenge 2013, held on April 21,
 * 2013.
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
#include <cstdio>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define trav(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
int main()
{
    int n, m; scanf("%d %d", &n, &m);

    vector<string> a(n);
    char c[101];
    rep(i,0,n)
    {
        scanf("%s", c);
        a[i] = c;
    }

    vector<string> b(m);
    rep(i,0,m)
    {
        scanf("%s", c);
        b[i] = c;
    }

    vi ans(m, -1);
    rep(i,0,n)
    {
        vi where(m, 0);
        vector<vi> who(26);
        rep(j,0,m) if (ans[j] == -1)
            who[b[j][0] - 'A'].push_back(j);

        rep(j,0,a[i].size())
        {
            vi oldwho = who[a[i][j] - 'a'];
            who[a[i][j] - 'a'].clear();
            rep(l,0,oldwho.size())
            {
                int w = oldwho[l];
                where[w]++;
                if (where[w] == 3)
                    ans[w] = i;
                else
                    who[b[w][where[w]] - 'A'].push_back(w);
            }
        }
    }

    rep(i,0,m)
    {
        if (ans[i] != -1)
            printf("%s\n", a[ans[i]].c_str());
        else
            printf("No valid word\n");
    }
}
