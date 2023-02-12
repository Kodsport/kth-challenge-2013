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
using System;
using System.Collections.Generic;
using System.Linq;

class Bank
{
    const int INF = -123456789;

    static void improvMax(ref int a, int b)
    {
        a = Math.Max(a, b);
    }

    public static void Main ()
    {
        string[] ss = Console.ReadLine().Split(' ');
        int n = int.Parse(ss[0]), t = int.Parse(ss[1]);

        List<List<int>> people =
            Enumerable.Range(0, t).Select( x => new List<int>() ).ToList();
        for (int i = 0; i < n; i++)
        {
            string[] tt = Console.ReadLine().Split(' ');
            int c = int.Parse(tt[0]), s = int.Parse(tt[1]);
            people[s].Add(c);
        }

        people = people.Select( p => p.OrderBy(x => -x).ToList() ).ToList();

        int[, ] best = new int[t + 1, t];
        for (int i = 0; i <= t; i++)
            for (int j = 0; j < t; j++)
                best[i, j] = INF;
        best[t, 0] = 0;

        for (int i = t; i > 0; --i)
            for (int j = 0; j < t; j++) if (best[i, j] != INF)
            {
                int sum = 0;
                for (int k = 0; k < people[i - 1].Count; k++)
                {
                    if (j + (int)k >= t) break;
                    sum += people[i - 1][k];
                    improvMax(ref best[i - 1, j + k], best[i, j] + sum);
                }
                improvMax(ref best[i - 1, Math.Max(j - 1, 0)], best[i, j]);
            }

        Console.WriteLine(best[0, 0]);
    }
}
