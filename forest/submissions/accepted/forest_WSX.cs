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
//Solution by WSX (Ján Oravec)
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Threading;

struct Point
{
    public Point (double x, double y)
    {
        this.x = x;
        this.y = y;
    }

    public Point (string s)
    {
        string[] ss = s.Split (' ');
        this = new Point (double.Parse (ss[0]), double.Parse (ss[1]));
    }

    public double x, y;
}

class Forest
{
    IEnumerable<Point> Move (IEnumerable<Point> p, double dx, double dy)
    {
        foreach (Point q in p)
            yield return new Point (q.x + dx, q.y + dy);
    }

    IEnumerable<Point> Rotate (IEnumerable<Point> p, double angle)
    {
        foreach (Point q in p)
            yield return new Point (q.x * Math.Cos (angle) - q.y * Math.Sin (angle), q.y * Math.Cos (angle) + q.x * Math.Sin (angle));
    }

    IEnumerable<Point> Cut (IEnumerable<Point> _p)
    {
        List<Point> p = new List<Point> (_p);
        p.Add (p[0]);

        for (int i = 1; i < p.Count; ++i)
        {
            Point a = p[i - 1];
            Point b = p[i];

            if (a.y * b.y < -1E-8)
                yield return new Point ((b.y * a.x - a.y * b.x) / (b.y - a.y), 0);

            if (b.y < 0)
                b.y = 0;

            yield return b;
        }
    }

    double Area (Point a, Point b)
    {
        return (a.x * b.y - b.x * a.y) / 2.0;
    }

    double Area (Point a, Point b, Point c)
    {
        return Area (new Point (b.x - a.x, b.y - a.y), new Point (c.x - a.x, c.y - a.y));
    }

    double Area (IEnumerable<Point> _p)
    {
        List<Point> p = new List<Point> (_p);

        double area = 0;

        for (int i = 2; i < p.Count; ++i)
            area += Area (p[0], p[i - 1], p[i]);

        return Math.Abs (area);
    }

    double Solve2 (IEnumerable<Point> p, Point a, Point b, double shift)
    {
        return Area (Cut (Move (Rotate (Move (p, -a.x, -a.y), -Math.Atan2 (b.y - a.y, b.x - a.x)), 0, -shift)));
    }

    public void Solve ()
    {
        int n = int.Parse (Console.ReadLine ());
        Point[] p = new Point[n];

        for (int i = 0; i < n; ++i)
            p[i] = new Point (Console.ReadLine ());

        string[] ss = Console.ReadLine ().Split (' ');

        Point a = new Point (double.Parse (ss[0]), double.Parse (ss[1]));
        Point b = new Point (double.Parse (ss[2]), double.Parse (ss[3]));

        double shift = double.Parse (Console.ReadLine ());

        Console.WriteLine (Solve2 (p, a, b, shift) + Solve2 (p, b, a, shift));
    }


    public static void Main ()
    {
        Thread.CurrentThread.CurrentCulture = System.Globalization.CultureInfo.InvariantCulture;
        new Forest ().Solve ();
    }
}
