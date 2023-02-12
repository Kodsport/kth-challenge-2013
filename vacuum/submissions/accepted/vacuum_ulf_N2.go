/* This is an example solution to the "Vacuum Tubes" problem from KTH Challenge 2013, held on April
 * 21, 2013.
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
import "sort"

func main() {
	var L1, L2, N int
	fmt.Scanf("%d%d%d",&L1, &L2, &N)
	tubes := make([]int,N)
	for i := range tubes {
		fmt.Scanf("%d",&tubes[i])
	}
	sort.Ints(tubes)
	best := -1;
	a := N-1;
	for i := range tubes {
		for a >= 0 && tubes[i]+tubes[a] > L1 { a-- }
		if a < 0 { break }
		for j := a; j > a-4 && j >= 0; j-- {
			if i == j { continue }
			b := N-1
			for k := range tubes {
				if k == i || k == j { continue }
				for b >= 0 && (tubes[k]+tubes[b] > L2 ||
						 b==i || b==j || b==k) { b-- }
				if b < 0 { break }
				if sum := tubes[i]+tubes[j]+tubes[k]+tubes[b]; sum > best {
					best = sum
				}
			}
		}
	}
	if best > -1 {
		fmt.Println(best)
	} else {
		fmt.Println("Impossible")
	}
}

