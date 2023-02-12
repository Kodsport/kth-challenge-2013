/* This is an example solution to the "Vacuum Tubes" problem from KTH Challenge 2013, held on April
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

class Vacuum
{
    public static void Main ()
    {
        string[] ss = Console.ReadLine().Split(' ');
        int[] l = new int[]{int.Parse(ss[0]), int.Parse(ss[1])};
        int n = int.Parse(ss[2]);

        List<int> a =
            Enumerable.Range(0, n)
            .Select(i => int.Parse(Console.ReadLine()))
            .OrderBy(x => x)
            .ToList();

        int[, ] other = new int[n + 1, 2];
        for (int k = 0; k < 2; k++)
            for (int i = 0; i < n; i++)
        {
            int u = (i == 0) ? n - 1 : other[i - 1, k];
            while (u >= 0 && a[u] + a[i] > l[k])
                u--;
            other[i, k] = u;
        }

        int res = -1;
        for (int i = 0; i < n; i++) if (other[i, 0] > i)
            for (int j = 0; j < n; j++) if (i != j && other[j, 1] > j)
                for (int k = other[i, 0]; k >= other[i, 0] - 3 && k > i; k--) if (k != j)
            {
                int v = other[j, 1];
                while (v == i || v == k || v == j) v--;
                if (v >= 0)
                    res = Math.Max(res, a[i] + a[k] + a[j] + a[v]);
            }

        if (res == -1)
            Console.WriteLine("Impossible");
        else
            Console.WriteLine(res);
    }
}
