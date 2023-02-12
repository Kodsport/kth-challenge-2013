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
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define rep(i,a,b) for(__typeof(b) i=a; i<(b); ++i)
#define repd(i,a,b) for(__typeof(b) i=a; i>=(b); --i)

typedef pair<bool, int> pbi;
vector<pbi> out;
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
bool a[50][50], b[50][50];
void rotate4(int i, int j, int k, int l)
{
    rot(j, i, l, n);
    rot(l, k, j, n);
    rot(j, l, i, n);
    rot(l, j, k, n);

    bool x[] = {a[i][j], a[k][l], a[j][l]};
    rotate(x, x + 1, x + 3);
    a[j][i] = a[i][j] = x[0];
    a[l][k] = a[k][l] = x[1];
    a[j][l] = a[l][j] = x[2];
}

void rotate3(int i, int j, int l) { rotate4(i, j, i, l); }

void fix(int i, int j, int dif)
{
    for (int l = j + dif; l < n && l >= 0; l += dif)
        if (b[i][j] == a[i][l])
    {
        rotate3(i, j, l);
        return;
    }

    for (int k = i + dif; k < n && k >= 0; k += dif)
        for (int l = k + dif; l < n && l >= 0; l += dif)
        if (l != j && b[i][j] == a[k][l])
        {
            if (j == k) rotate3(i, l, j);
            else rotate4(i, j, l, k);
            return;
        }
}

int main()
{
    scanf("%d %d", &n, &m);
    rep(k,0,2) rep(i,0,m)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        if (k) b[y][x] = b[x][y] = true;
        else a[y][x] = a[x][y] = true;
    }

    rep(iter,0,4)
    {
        rep(i,0,n) rep(j,i+1,n)
            if (a[i][j] != b[i][j])
                fix(i, j, 1);

        //fix the last node
        repd(i,n-1,0) repd(j,i-1,0)
            if (a[i][j] != b[i][j])
                fix(i, j, -1);
    }

    printf("%d\n", (int)out.size());
    for (auto x : out)
        printf("%s %d\n", x.first ? "R" : "G", x.second);
}
