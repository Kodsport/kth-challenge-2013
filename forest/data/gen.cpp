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
#include <complex>
using namespace std;

#define REP(i,n) for(__typeof(n) i=0; i<(n); ++i)
#define FOR(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define FOREACH(it,c) for(__typeof((c).begin()) it=(c).begin(); it!=(c).end(); ++it)
typedef complex<int> bod;

bod t[4] = {bod(0, 1), bod(1, 0), bod(0, -1), bod(-1, 0)};
int a[4000][4000], s;
void dfs(bod x)
{
    a[real(x)][imag(x)] = 0;
    int e[4];
    REP(i,4) e[i] = i;
    REP(i,4)
    {
        int q = rand() % (4 - i) + i;
        swap(e[q], e[i]);
    }

    REP(k,4)
    {
        bod y = x + 2 * t[e[k]];
        if (real(y) < 0 or real(y) >= s or imag(y) < 0 or imag(y) >= s)
            continue;
        if (a[real(y)][imag(y)] == 0)
            continue;
        bod q = x + t[e[k]];
        a[real(q)][imag(q)] = 2;
        dfs(y);
    }
}
int size;
typedef pair<int, int> PI;
map<PI, vector<PI> > g;
void vloz(bod x, bod y)
{
    g[PI(real(x), imag(x))].push_back(PI(real(y), imag(y)));
    g[PI(real(y), imag(y))].push_back(PI(real(x), imag(x)));
}
void kresli(bod f[4], bool y)
{
    bool k1 = real(f[0]) >= 0 and imag(f[0]) >= 0,
         k2 = real(f[3]) < size and imag(f[3]) < size;
    if (k1) vloz(f[0], f[2 - y]);
    if (k2) vloz(f[1 + y], f[3]);
}
int main()
{
    scanf("%d", &s);
    s = (int) sqrt(s);
    s = 2 * s + 1;
    srand(time(0));
    int dl = 12;
    REP(i,s) REP(j,s)
        a[i][j] = 1;
    dfs(bod(1, 1));
    size = (s / 2) * dl;

    REP(i,s) REP(j,s)
    {
        if (i % 2 == 0 and j % 2 == 0)
            continue;
        if (a[i][j] != 0)
        {
            bod e, f[4];
            if (i % 2 == 1)
            {
                e = bod((j / 2 - 1) * dl + 3 * dl / 4, (i / 2) * dl + dl / 4);
                REP(k,4)
                    f[k] = bod(real(e) + (k / 2) * dl / 2, imag(e) + (k % 2) * dl / 2);
                kresli(f, a[i][j] == 1);
            }
            else
            {
                e = bod((j / 2) * dl + dl / 4, (i / 2 - 1) * dl + 3 * dl / 4);
                REP(k,4)
                    f[k] = bod(real(e) + (k / 2) * dl / 2, imag(e) + (k % 2) * dl / 2);
                kresli(f, a[i][j] == 2);
            }
        }
    }

    vector<PI> zoz, novy;
    zoz.push_back(g.begin()->first);
    zoz.push_back(g[zoz.back()][0]);
    while (zoz[0] != zoz.back())
    {
        FOREACH(x,g[zoz.back()])
        {
            if (*x != zoz[zoz.size() - 2])
            {
                zoz.push_back(*x);
                break;
            }
        }
    }

    zoz.pop_back();
    REP(i,zoz.size())
    {
        PI a = zoz[(i + zoz.size() - 1) % zoz.size()],
           b = zoz[(i + 1) % zoz.size()];
        if (a.first == b.first || a.second == b.second)
            continue;
        novy.push_back(zoz[i]);
    }
    REP(i,novy.size())
        cout << novy[i].first << " " << novy[i].second << endl;
}
