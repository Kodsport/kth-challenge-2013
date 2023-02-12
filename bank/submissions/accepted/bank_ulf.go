/* This is an example solution to the "Bank Queue" problem from KTH Challenge 2013, held on April 21,
 * 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Ulf Lundstrom

package main

import "fmt"
import "sort"

type customer struct {
	c, t int
}
type queue []customer
func (q queue) Len() int {
    return len(q)
}
func (q queue) Less(i, j int) bool {
    return q[i].c > q[j].c
}
func (q queue) Swap(i, j int) {
    q[i], q[j] = q[j], q[i]
}


func main() {
	var N, T int
	fmt.Scanf("%d%d", &N, &T)
	q := make(queue,N)
	for i := range q {
		fmt.Scanf("%d%d", &q[i].c, &q[i].t)
	}
	sort.Sort(q)
	sum := 0
	taken := make([]bool,T)
	for i := range(q) {
		time := q[i].t
		for ; time >= 0; time-- {
			if !taken[time] {
				sum += q[i].c
				taken[time] = true
				break
			}
		}
	}
	fmt.Println(sum)
}

