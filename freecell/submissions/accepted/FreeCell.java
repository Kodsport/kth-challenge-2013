/* This is an example solution to the "Free Cell" problem from KTH Challenge 2013, held on April 21,
 * 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Andreas Lundblad
public class FreeCell {

  public static int computeMax(int emptyCells, int emptyCols) {
    int max = emptyCells + 1;
    while (--emptyCols >= 0)
      max += computeMax(emptyCells, emptyCols);
    return max;
  }

  public static void main(String[] args) {
    java.util.Scanner s = new java.util.Scanner(System.in);

    boolean solveable = computeMax(s.nextInt(), s.nextInt()) >= s.nextInt();
    System.out.println(solveable ? "yes" : "no");
  }
}
