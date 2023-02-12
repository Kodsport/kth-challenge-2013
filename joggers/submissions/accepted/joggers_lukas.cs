/* This is an example solution to the "Chicken Joggers" problem from KTH Challenge 2013, held on
 * April 21, 2013.
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

class Joggers
{
    static List<bool> seen, lamp;
    static int[, ] best;
    static List<List<Tuple<int, int>>> g;

    static void dfs(int u, int dist)
    {
        seen[u] = true;
        var sons = g[u].Where(x => !seen[x.Item1]);
        best[u, 0] = dist == 0 || sons.All(x => x.Item2 <= dist || lamp[x.Item1]) ? 0 : g.Count + 47;
        best[u, 1] = Convert.ToInt32(!lamp[u]);

        foreach (Tuple<int, int> edge in sons.Where(x => dist >= x.Item2))
        {
            dfs(edge.Item1, dist - edge.Item2);
            best[u, 0] += best[edge.Item1, 1];
            best[u, 1] += Math.Min(best[edge.Item1, 0], best[edge.Item1, 1]);
        }
    }

    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        string[] ss = reader.ReadLine().Split(' ');
        int n = int.Parse(ss[0]), s = int.Parse(ss[1]);

        g = Enumerable.Range(0, n).Select(x => new List<Tuple<int, int>> ()).ToList();
        for (int i = 0; i < n - 1; i++)
        {
            string[] tt = reader.ReadLine().Split(' ');
            int a = int.Parse(tt[0]), b = int.Parse(tt[1]), c = int.Parse(tt[2]);
            a--; b--;
            g[a].Add(Tuple.Create(b, 2 * c));
            g[b].Add(Tuple.Create(a, 2 * c));
        }

        best = new int[n, 2];
        foreach (int i in Enumerable.Range(0, n))
            foreach (int j in Enumerable.Range(0, 2))
                best[i, j] = n + 47;

        seen = Enumerable.Repeat(false, n).ToList();
        lamp = Enumerable.Repeat(false, n).ToList();
        int l = int.Parse(reader.ReadLine());
        if (l > 0)
            foreach (int x in reader.ReadLine().Split().Select(y => int.Parse(y)))
                lamp[x - 1] = true;

        dfs(0, s);
        Console.WriteLine(Math.Min(best[0, 0], best[0, 1]));
    }
}
