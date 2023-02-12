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
//Solution by Oskar Werkelin Ahlin

import java.util.Scanner;
import java.util.TreeMap;
import java.util.ArrayList;
import java.util.Map;

public class BankOskar {
    public class Bucket extends ArrayList<Integer> { }

    public BankOskar() {
        solve();
    }

    public void solve() {
        int N, T;
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        T = sc.nextInt();
        Bucket[] buckets = new Bucket[T];
        for (int i = 0; i < T; ++i) buckets[i] = new Bucket();
        for (int i = 0; i < N; ++i) {
            int ci, ti;
            ci = sc.nextInt();
            ti = sc.nextInt();
            buckets[ti].add(ci);
        }
        int answer = 0;
        TreeMap<Integer,Integer> active = new TreeMap<Integer,Integer>();
        for (int i = T-1; i >= 0; --i) {
            for (int x : buckets[i]) {
                int prevValue = 0;
                if (active.containsKey(x)) {
                    prevValue = active.get(x);
                }
                active.put(x, prevValue + 1);
            }
            if (!active.isEmpty()) {
                Map.Entry<Integer,Integer> lastPair = active.pollLastEntry();
                int newValue = (int)lastPair.getValue() - 1;
                if (newValue != 0) active.put(lastPair.getKey(), newValue);
                answer += lastPair.getKey();
            }
        }
        System.out.println(answer);
    }

    public static void main(String... args) {
        new BankOskar();
    }
}
