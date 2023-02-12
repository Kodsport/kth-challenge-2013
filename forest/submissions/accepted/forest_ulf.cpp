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
//Solution by Ulf Lundström
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double eps = 1e-10;
struct Point {
    typedef Point P;
    typedef const P & R;
    double x, y;
    explicit Point(double _x, double _y) :x(_x), y(_y) {};
    P operator-(R p) const { return P(x-p.x,y-p.y); }
    P operator*(double d) const { return P(x*d,y*d); }
    double dot(R p) const { return x*p.x+y*p.y; }
    double cross(R p) const { return x*p.y-y*p.x; }
    double dist() const { return sqrt(x*x+y*y); }
};
istream & operator>>(istream & is, Point & p) {
    is >> p.x >> p.y;
    return is;
}

Point O(0,0);

bool left(Point p, Point a, Point b) {
    return (b-a).cross(p-a) >= 0;
}

Point intersection(Point p1, Point p2, Point a, Point b) {
    double x = (p2-p1).cross(b-a);
    if (abs(x) < eps) return p2;
    return a-(b-a)*(p2-p1).cross(a-p1)*(1/x);
}

double area(Point p1, Point p2, Point p3) {
    return (p2-p1).cross(p3-p1);
}

//Calculates the area of the triangle (0,p1,p2) that lies left of the line (a,b)
double areaLeft(Point p0, Point p1, Point p2, Point a, Point b) {
    double A = area(p0,p1,p2);
    if (!left(p0,a,b)) {
	return A-areaLeft(p0,p1,p2,b,a);
    }
    if (left(p1,a,b)) {
	if (left(p2,a,b)) {
	    return A;
	}
	Point p3 = intersection(p2,p0,a,b);
	Point p4 = intersection(p2,p1,a,b);
	return A-area(p2,p3,p4);
    } else {
	if (left(p2,a,b)) {
	    Point p3 = intersection(p1,p2,a,b);
	    Point p4 = intersection(p1,p0,a,b);
	    return A-area(p1,p3,p4);
	} else {
	    Point p3 = intersection(p0,p1,a,b);
	    Point p4 = intersection(p0,p2,a,b);
	    return area(p0,p3,p4);
	}
    }
}

double areaLeft(vector<Point> v, Point a, Point b) {
    double A = 0;
    for (int i = 0, j = v.size()-1; i < v.size(); ++i, j=i-1) {
	A += areaLeft(O, v[i], v[j], a, b);
    }
    return A;
}

double area(vector<Point> v) {
    double A;
    for (int i = 0, j = v.size()-1; i < v.size(); ++i, j=i-1) {
	A += area(O,v[i],v[j]);
    }
    return A;
}


int main() {
    int N;
    cin >> N;
    vector<Point> v(N,Point(0,0));
    for (int i = 0; i < N; ++i)
	cin >> v[i];
    Point a0(0,0),b0(0,0);
    cin >> a0 >> b0;

    double d;
    cin >> d;
    Point t = (a0-b0)*(d/(a0-b0).dist());
    t = Point(-t.y,t.x);
    Point a = a0-t;
    Point b = b0-t;
    double A1 = areaLeft(v,a,b);
    a = b0-t*-1;
    b = a0-t*-1;
    double A2 = areaLeft(v,a,b);

    cout.precision(12);
    cout << abs(A1+A2)/2 << endl;
}
