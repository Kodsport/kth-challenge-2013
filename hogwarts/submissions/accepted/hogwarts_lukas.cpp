/* This is an example solution to the "Hogwarts" problem from KTH Challenge 2013, held on April 21,
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
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <bitset>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define repd(i,a,b) for(__typeof(b) i=a; i>=(b); --i)

typedef pair<bool, int> pbi;
typedef pair<int, int> pii;
typedef vector<pbi> vbi;
vbi out;
typedef vector<int> vi;
void rot(int a, int b, int c, int n)
{
    b -= (b >= a);
    c -= (c >= a);
    n--;
    int dis = (c - b + n) % n;
    if (dis < n - dis)
        rep(i,0,dis) out.push_back(pbi(true, a));
    else
        rep(i,0,n-dis) out.push_back(pbi(false, a));
}

int n, m;
void rotate4(int i, int j, int k, int l, vector<vector<bool> > &a)
{
    rot(j, i, l, n);
    rot(l, k, j, n);
    rot(j, l, i, n);
    rot(l, j, k, n);

    bool x[] = {a[i][j], a[k][l], a[j][l]};
    a[j][i] = a[i][j] = x[1];
    a[l][k] = a[k][l] = x[2];
    a[j][l] = a[l][j] = x[0];
}

void rotate3(int i, int j, int l, vector<vector<bool> > &a) { rotate4(i, j, i, l, a); }

void fix(int i, int j, int dif, vector<vector<bool> > &a, vector<vector<bool> > &b)
{
    for (int l = j + dif; l < n && l >= 0; l += dif)
        if (b[i][j] == a[i][l])
    {
        rotate3(i, j, l, a);
        return;
    }

    for (int k = i + dif; k < n && k >= 0; k += dif)
        for (int l = k + dif; l < n && l >= 0; l += dif)
        if (l != j && b[i][j] == a[k][l])
        {
            if (j == k) rotate3(i, l, j, a);
            else rotate4(i, j, l, k, a);
            return;
        }
}

int encode(vector<vector<bool> > &a)
{
    bitset<21> b;
    int u = 0;
    rep(i,0,n) rep(j,i+1,n)
        b[u++] = a[i][j];
    return b.to_ulong();
}

vector<int> pred;
vector<bool> seen;
vector<vbi> op;
void search(vector<vector<bool> > a, vbi ops, vector<vector<bool> > fat)
{
    int oo = encode(a);
    if (seen[oo]) return;
    seen[oo] = true;
    pred[oo] = encode(fat);
    op[oo] = ops;

    vector<vector<bool> > bak = a;
    rep(i,0,n) rep(j,i+1,n) rep(l,i+1,n) if (l != j)
    {
        a = bak;
        out.clear();
        rotate3(i, j, l, a);
        search(a, out, bak);
    }
}

void init_edges(vector<pii> edges[], int q, vector<vector<bool> > &a, vector<vector<bool> > &b)
{
    a.assign(n, vector<bool> (n));
    b.assign(n, vector<bool> (n));
    rep(k,0,2) rep(i,0,m)
    {
        int x = edges[k][i].first, y = edges[k][i].second;
        x = (x + q) % n; y = (y + q) % n;
        if (k) b[y][x] = b[x][y] = true;
        else a[y][x] = a[x][y] = true;
    }
}

int main()
{
    scanf("%d %d", &n, &m);
    vector<pii> edges[2];
    rep(k,0,2) rep(i,0,m)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        edges[k].push_back(pii(x, y));
    }

    vector<vector<bool> > a, b;
    rep(iter,0,16)
    {
        int q = rand() % n; // randomly rotate, so that there are no problems with the last vertex
        init_edges(edges, q, a, b);

        out.clear();
        if (n == 3)//degenerate case
        {
            rep(i,0,n) rep(j,i+1,n)
                if (a[i][j] != b[i][j])
                    rotate3(0, 1, 2, a);
        }
        else
        {
            rep(i,0,n) rep(j,i+1,n)
                if (a[i][j] != b[i][j])
                    fix(i, j, 1, a, b);

            //fix the last node
            repd(i,n-1,0) repd(j,i-1,0)
                if (a[i][j] != b[i][j])
                    fix(i, j, -1, a, b);
        }

        bool ok = true;
        rep(i,0,n) rep(j,i+1,n)
            if (a[i][j] != b[i][j]) ok = false;

        if (ok)
        {
            printf("%d\n", (int)out.size());
            for (auto x : out)
                printf("%s %d\n", x.first ? "R" : "G", (x.second + n - q) % n);
            return 0;
        }
    }

    // we failed, let's try brute force approach
    init_edges(edges, 0, a, b);
    assert(n <= 7);//otherwise we are screwed, but it shouldn't happen
    int cnt = n * (n - 1) / 2;
    pred.assign(1 << cnt, -1);
    seen.assign(1 << cnt, 0);
    op.assign(1 << cnt, vbi());
    search(a, vbi(), a);

    out.clear();
    int u = encode(b), v = encode(a);
    assert(seen[u]);
    for (int u = encode(b); u != v; u = pred[u])
        repd(i,op[u].size()-1,0)
            out.push_back(pbi(op[u][i].first, op[u][i].second));

    reverse(out.begin(), out.end());
    printf("%d\n", (int)out.size());
    for (auto x : out)
        printf("%s %d\n", x.first ? "R" : "G", x.second);
}
