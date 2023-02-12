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
//Solution by Ulf Lundström

package main

import "fmt"

func main() {
	var n,m,k int
	fmt.Scanf("%d%d%d",&n,&m,&k)
	if k <= (n+1)<<uint(m) {
		fmt.Println("yes")
	} else {
		fmt.Println("no")
	}
}

