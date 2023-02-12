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
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;

class Hogwarts
{
    static int n, m, q;
    static IEnumerable<Tuple<bool, int>> rot(int a, int b, int c, int n)
    {
        b -= Convert.ToInt32(b >= a);
        c -= Convert.ToInt32(c >= a);
        n--;
        int dis = (c - b + n) % n;
        int dis2 = Math.Min(dis, n - dis);

        return Enumerable.Repeat(Tuple.Create(dis < n - dis, (a - q + n + 1) % (n + 1)), dis2);
    }

    static List<Tuple<bool, int>> rotate4(int i, int j, int k, int l, bool[, ] a)
    {
        List<Tuple<bool, int>> res = new List<Tuple<bool, int>> ();
        res.AddRange( rot(j, i, l, n) );
        res.AddRange( rot(l, k, j, n) );
        res.AddRange( rot(j, l, i, n) );
        res.AddRange( rot(l, j, k, n) );

        bool[] x = new bool[]{a[i, j], a[k, l], a[j, l]};
        a[j, i] = a[i, j] = x[1];
        a[l, k] = a[k, l] = x[2];
        a[j, l] = a[l, j] = x[0];
        return res;
    }

    static List<Tuple<bool, int>> rotate3(int i, int j, int l, bool[, ] a)
    {
        return rotate4(i, j, i, l, a);
    }

    static void fix(int i, int j, int dif, bool[, ] a, bool[, ] b, List<Tuple<bool, int>> outt)
    {
        for (int l = j + dif; l < n && l >= 0; l += dif)
            if (b[i, j] == a[i, l])
        {
            outt.AddRange( rotate3(i, j, l, a) );
            return;
        }

        for (int k = i + dif; k < n && k >= 0; k += dif)
            for (int l = k + dif; l < n && l >= 0; l += dif)
            if (l != j && b[i, j] == a[k, l])
            {
                if (j == k) outt.AddRange( rotate3(i, l, j, a) );
                else outt.AddRange( rotate4(i, j, l, k, a) );
                return;
            }
    }

    static int encode(bool[, ] x)
    {
        int res = 0, u = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++, u++)
            res |= Convert.ToInt32(x[i, j]) << u;
        return res;
    }

    static List<int> pred;
    static List<bool> seen;
    static List<List<Tuple<bool, int>>> op;
    static void search(bool[, ] a, List<Tuple<bool, int>> ops, int fat)
    {
        int oo = encode(a);
        if (seen[oo]) return;
        seen[oo] = true;
        pred[oo] = fat;
        ops.Reverse();
        op[oo] = ops;

        bool[, ] bak = (bool[, ])a.Clone();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int l = i + 1; l < n; l++) if (j != l)
        {
            Array.Copy(bak, a, n * n);
            List<Tuple<bool, int>> tmp = rotate3(i, j, l, a);
            search(a, tmp, encode(bak));
        }
    }

    static void InitEdges(List<List<Tuple<int, int>>> edges, bool[, ] a, bool[, ] b)
    {
        Array.Clear(a, 0, n * n); Array.Clear(b, 0, n * n);
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < m; i++)
        {
            int x = edges[k][i].Item1, y = edges[k][i].Item2;
            x = (x + q) % n; y = (y + q) % n;
            if (k == 1) b[y, x] = b[x, y] = true;
            else a[y, x] = a[x, y] = true;
        }
    }

    static void Print(List<Tuple<bool, int>> outt)
    {
        Console.WriteLine(outt.Count);
        foreach (var x in outt)
            Console.WriteLine((x.Item1 ? "R " : "G ") + x.Item2);
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        string[] ss = reader.ReadLine().Split(' ');
        n = int.Parse(ss[0]); m = int.Parse(ss[1]);

        List<List<Tuple<int, int>>> edges =
            Enumerable.Range(0, 2).Select(x => new List<Tuple<int, int>> ()).ToList();

        for (int k = 0; k < 2; k++) for (int i = 0; i < m; i++)
        {
            string[] tt = reader.ReadLine().Split(' ');
            int aa = int.Parse(tt[0]), bb = int.Parse(tt[1]);
            edges[k].Add(Tuple.Create(aa, bb));
        }

        bool[, ] a = new bool[n, n];
        bool[, ] b = new bool[n, n];

        Random random = new Random();
        List<Tuple<bool, int>> outt;
        foreach (int iter in Enumerable.Range(0, 29))
        {
            q = random.Next(0, n);
            InitEdges(edges, a, b);

            outt = new List<Tuple<bool, int>> ();
            if (n == 3)//degenerate case
            {
                foreach (int i in Enumerable.Range(0, n))
                    for (int j = i + 1; j < n; j++)
                        if (a[i, j] != b[i, j])
                            outt.AddRange( rotate3(0, 1, 2, a) );
            }
            else
            {
                foreach (int i in Enumerable.Range(0, n))
                    for (int j = i + 1; j < n; j++)
                        if (a[i, j] != b[i, j])
                            fix(i, j, 1, a, b, outt);

                //fix the last node
                for (int i = n - 1; i >= 0; i--)
                    for (int j = i - 1; j >= 0; j--)
                        if (a[i, j] != b[i, j])
                            fix(i, j, -1, a, b, outt);
            }

            bool nok = (
                from i in Enumerable.Range(0, n)
                from j in Enumerable.Range(0, n)
                where a[i, j] != b[i, j] select 1
                ).Any();

            if (!nok)
            {
                Print(outt);
                return;
            }
        }

        // we failed, let's try brute force approach
        q = 0;
        InitEdges(edges, a, b);
        int cnt = n * (n - 1) / 2;
        pred = Enumerable.Repeat(0, 1 << cnt).ToList();
        seen = Enumerable.Repeat(false, 1 << cnt).ToList();
        op = Enumerable.Range(0, 1 << cnt).Select(x => new List<Tuple<bool, int>> ()).ToList();
        int v = encode(a);
        search(a, new List<Tuple<bool, int>> (), -1);

        outt = new List<Tuple<bool, int>> ();
        for (int u = encode(b); u != v; u = pred[u])
            outt.AddRange(op[u]);
        outt.Reverse();
        Print(outt);
    }
}
