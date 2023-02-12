/* This is an example solution to the "Car Game" problem from KTH Challenge 2013, held on April 21,
 * 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Ulf Lundström
import java.util.Scanner;
import java.io.*;

public class CargameUlf {
	public static void main(String[] args) {
		Scanner sc = new Scanner(new BufferedInputStream(System.in));
		int N = sc.nextInt();
		int M = sc.nextInt();
		int S = 'z'-'a'+1;
		boolean[] one = new boolean[S];
		boolean[][] two = new boolean[S][S];
		int[][][] three = new int[S][S][S];
		for (int i = 0; i < S; ++i) {
			for (int j = 0; j < S; ++j) {
				for (int k = 0; k < S; ++k) {
					three[i][j][k] = -1;
				}
			}
		}
		String[] words = new String[N];

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < S; ++j) {
				one[j] = false;
				for (int k = 0; k < S; ++k) {
					two[j][k] = false;
				}
			}
			String word = sc.next();
			for (int j = 0; j < word.length(); ++j) {
				for (int k = 0; k < S; ++k) {
					for (int l = 0; l < S; ++l) {
						if (two[k][l] && three[k][l][word.charAt(j)-'a'] == -1)
							three[k][l][word.charAt(j)-'a'] = i;
					}
					two[k][word.charAt(j)-'a'] |= one[k];
				}
				one[word.charAt(j)-'a'] = true;
			}
			words[i] = word;
		}
		for (int i = 0; i < M; ++i) {
			String plate = sc.next();
			int a = three[plate.charAt(0)-'A'][plate.charAt(1)-'A'][plate.charAt(2)-'A'];
			if (a == -1)
				System.out.println("No valid word");
			else
				System.out.println(words[a]);
		}
	}
}
