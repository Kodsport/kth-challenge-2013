/* This is an example solution to the "Flag Quiz" problem from KTH Challenge 2013, held on April
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

class FlagQuiz
{
    private static int Dist(string[] a, string[] b)
    {
        // Zip doesn't compile with .Net < 4.0
        return a.Zip(b, (c, d) => Convert.ToInt32(c != d)).Sum();
        // return Enumerable.Range(0, a.Length).Sum(i => Convert.ToInt32(a[i] != b[i]));
    }

    public static void Main ()
    {
        Console.ReadLine();
        int n = int.Parse(Console.ReadLine());

        var flags =
            Enumerable.Range(0, n)
            .Select(i => Console.ReadLine().Split(new string[]{", "}, StringSplitOptions.None))
            .ToList();

        var res =
            (from flag in flags
            select new { Flag = flag, Distance = (from h in flags select Dist(h, flag)).Max() })
            .OrderBy(x => x.Distance);

        Console.WriteLine(string.Join(", ", res.First().Flag));
    }
}
