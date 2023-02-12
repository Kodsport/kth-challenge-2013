/* This is an example solution to the "Forest Highway" problem from KTH Challenge 2013, held on
 * April 21, 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Marc Vinyals
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
const double EPS=1e-9;

class pt {
public:
  double x,y;
  pt() {}
  pt(double x_, double y_) : x(x_), y(y_) {}
  pt operator + (const pt& p) const { return pt(x+p.x,y+p.y); }
  pt operator - (const pt& p) const { return pt(x-p.x,y-p.y); }
  pt operator * (double z) const { return pt(x*z,y*z); }
  pt operator / (double z) const { return pt(x/z,y/z); }
  double operator ^ (const pt& v) const { return x*v.y-y*v.x; }
  void cossin(double& c, double& s) const {
    double h=hypot(x,y);
    c=x/h;
    s=y/h;
  }
  pt rotate(double c, double s) const { return pt(x*c-y*s,y*c+x*s); }
  pt operator - () const { return pt(-x,-y); }
  pt operator ~ () const { return pt(-y,x); }
  double mod() { return hypot(x,y); }
  double mod2() { return x*x+y*y; }
};

bool left(const pt& v, const pt& w) { return (v^w) > EPS; }

pt intersect(const pt& p, const pt& v, const pt& q, const pt& w) {
  double lambda = ((q-p)^w)/(v^w);
  return p+v*lambda;
}

istream& operator >> (istream& i, pt& p) {
  return i >> p.x >> p.y;
}
ostream& operator << (ostream& o, const pt& p) {
  return o << '(' << p.x << ',' << p.y << ')';
}

typedef vector<pt> VP;

double area(const VP& v) {
  int n=v.size();
  double ret=0;
  FOR (i,0,n) {
    ret+=(v[i]^v[(i+1)%n]);
  }
  return abs(ret/2);
}

int main() {
  int n;
  cin >> n;
  VP poly(n);
  FOR (i,0,n) cin >> poly[i];
  pt a,b;
  cin >> a >> b;
  pt v=b-a;
  double d;
  cin >> d;
  VP polyup,polydown;

#if 0
  double c,s;
  (b-a).cossin(c,s);
  FOR (i,0,n) poly[i]=(poly[i]-a).rotate(c,-s);
  
  FOR (i,0,n) {
    if (poly[i].y>=d) polyup.push_back(poly[i]);
    if ((poly[i].y<d) ^ (poly[(i+1)%n].y<d)) {
      polyup.push_back(intersect(pt(0,d),pt(1,0),poly[i],poly[(i+1)%n]-poly[i]));
    }
  }
  FOR (i,0,n) {
    if (poly[i].y<=-d) polydown.push_back(poly[i]);
    if ((poly[i].y>-d) ^ (poly[(i+1)%n].y>-d)) {
      polydown.push_back(intersect(pt(0,-d),pt(1,0),poly[i],poly[(i+1)%n]-poly[i]));
    }
  }
#endif
  
  pt w=(~v)*(d/v.mod());
  FOR (i,0,n) {
    if (!left(-v,poly[i]-(a+w))) polyup.push_back(poly[i]);
    if (left(-v,poly[i]-(a+w)) ^ left(-v,poly[(i+1)%n]-(a+w))) {
      polyup.push_back(intersect(a+w,v,poly[i],poly[(i+1)%n]-poly[i]));
    }
  }
  FOR (i,0,n) {
    if (!left(v,poly[i]-(a-w))) polydown.push_back(poly[i]);
    if (left(v,poly[i]-(a-w)) ^ left(v,poly[(i+1)%n]-(a-w))) {
      polydown.push_back(intersect(a-w,v,poly[i],poly[(i+1)%n]-poly[i]));
    }
  }
  
  printf("%.15f\n",area(polyup)+area(polydown));
}
