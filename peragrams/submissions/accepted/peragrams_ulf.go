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
//Solution by Ulf Lundström

package main

import "fmt"

func max(a, b int) int {
	if (a > b) {
		return a
	}
	return b
}

func main() {
	var s string
	fmt.Scanf("%s",&s)
	m := make(map[uint8]int)
	for i := 0; i < len(s); i++ {
		m[s[i]]++
	}
	odd := 0;
	for _, val := range(m) {
		odd += val&1
	}
	fmt.Println(max(0,odd-1))
}

