/* This is an example solution to the "Forest Highway" problem from KTH Challenge 2013, held on April 21,
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
#include <cstdio>
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;

#define REP(i,n) for(__typeof(n) i=0; i<(n); ++i)

typedef complex<double> point;
double calc(point s, point t, double f)
{
    double p = (f - imag(s)) / (imag(t) - imag(s));
    return (1 - p) * real(s) + p * real(t);
}
double area(point s, point t)
{
    return (real(s) + real(t)) * (imag(t) - imag(s)) / 2;
}
int main()
{
    int n; scanf("%d", &n);
    vector<point> a(n);
    REP(i,n)
    {
        double x, y;
        scanf("%lf %lf", &x, &y);
        a[i] = point(x, y);
    }

    double x1, x2, y1, y2;
    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    point u = point(x1, y1), v = point(x2, y2);
    double d;
    scanf("%lf", &d);

    point r = u - v;
    double len = abs(r);
    r = point(real(r) / len, -imag(r) / len);

    // rotate vertically
    REP(i,n) a[i] *= r;
    u *= r; v *= r;

    double res = 0;
    REP(i,n)
    {
        int zn = 1;
        point s = a[i], t = a[(i + 1) % n];
        if (imag(s) > imag(t))
        {
            swap(s, t);
            zn = -1;
        }

        double f[] = {max(imag(s), min(imag(u) - d, imag(t))),
                      min(imag(t), max(imag(u) + d, imag(s)))};
        double r[] = {calc(s, t, f[0]), calc(s, t, f[1])};
        res += zn * (area(s, point(r[0], f[0])) + area(point(r[1], f[1]), t));
    }

    printf("%.9lf\n", abs(res));
}
