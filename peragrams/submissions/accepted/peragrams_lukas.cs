/* This is an example solution to the "Peragrams" problem from KTH Challenge 2013, held on April 21,
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
using System.Linq;

class Peragrams
{
    public static void Main ()
    {
        bool[] count = new bool[256];
        foreach (char c in Console.ReadLine())
            count[(int)c] ^= true;
        Console.WriteLine(Math.Max(0, count.Count(x => x) - 1));
    }
}
