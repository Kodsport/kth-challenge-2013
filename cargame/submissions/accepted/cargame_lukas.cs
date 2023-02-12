/* This is an example solution to the "Car Game" problem from KTH Challenge 2013, held on April
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
using System.IO;
using System.Collections.Generic;
using System.Linq;

class CarGame
{
    public static void Main ()
    {
        var bs = new BufferedStream(Console.OpenStandardInput());
        StreamReader reader = new StreamReader(bs);

        string[] ss = reader.ReadLine().Split();
        int n = int.Parse(ss[0]), m = int.Parse(ss[1]);

        var a = Enumerable.Range(0, n).Select(x => reader.ReadLine()).ToList();
        var b = Enumerable.Range(0, m).Select(x => reader.ReadLine()).ToList();

        List<int> ans = Enumerable.Repeat(-1, m).ToList();
        List<int> cand = Enumerable.Range(0, m).ToList();
        List<int> invCand = Enumerable.Range(0, m).ToList();
        List<int> where = Enumerable.Repeat(0, m).ToList();

        List<List<int>> who = Enumerable.Range(0, 26).Select(x => new List<int>()).ToList();
        for (int i = 0; i < n; i++)
        {
            foreach (var x in who) x.Clear();
            for (int j = 0; j < cand.Count; j++)
            {
                who[b[cand[j]][0] - 'A'].Add(cand[j]);
                where[j] = 0;
            }

            foreach (char x in a[i])
            {
                List<int> oldwho = new List<int> (who[x - 'a']);
                who[x - 'a'].Clear();
                foreach (int w in oldwho)
                {
                    int pos = invCand[w];
                    if (++where[pos] == 3)
                    {
                        ans[w] = i;
                        // remove w from cand
                        int last = cand.Last();
                        invCand[last] = pos;
                        cand[pos] = last;
                        where[pos] = where.Last();
                        cand.RemoveAt(cand.Count - 1);
                        where.RemoveAt(where.Count - 1);
                    }
                    else
                        who[b[w][where[pos]] - 'A'].Add(w);
                }
            }
        }

        foreach (int x in ans)
            Console.WriteLine(x != -1 ? a[x] : "No valid word");
    }
}
