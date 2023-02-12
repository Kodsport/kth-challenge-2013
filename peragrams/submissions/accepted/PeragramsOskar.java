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
//Solution by Oskar Werkelin Ahlin
import java.util.Scanner;

public class PeragramsOskar {
    public static void main(String ... args) {

        Scanner sc = new Scanner(System.in);
        int[] counts = new int[26];
        String str = sc.next();

        for (int i = 0; i < str.length(); ++i) {
            counts[str.charAt(i)-'a'] += 1;
        }

        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            if (counts[i] % 2 == 1) ++ans;
        }
        --ans;

        if (ans < 0) System.out.println(0);
        else System.out.println(ans);
    }
}
