/* This is an example solution to the "Chicken Joggers" problem from KTH Challenge 2013, held on
 * April 21, 2013.
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

import "bufio"
import "fmt"
import "os"
import "strings"
import "strconv"

type edge struct {
	to, dist int
}

var E [][]edge
var lamp []bool

func rec(from, to, dist int) (N int, extra bool) {
	extra = !lamp[to]
	if dist <= 0 {
		return
	}
	for _, next := range E[to] {
		if next.to != from {
			n, e := rec(to, next.to, dist-next.dist)
			N += n
			if e && extra {
				N++
				extra = false
			}
		}
	}
	return
}

func main() {
	var N, L, S int
    rdr := bufio.NewReader(os.Stdin)

    str, _ := rdr.ReadString('\n')
    arr := strings.Split(str, " ")
    N, _ = strconv.Atoi(arr[0])
    S, _ = strconv.Atoi(strings.TrimSpace(arr[1]))

	E = make([][]edge,N)
	for i := range E {
		E[i] = nil
	}
	for i := 0; i < N-1; i++ {
		var A,B,D int
		//fmt.Scanf("%d%d%d",&A,&B,&D)
        str, _ := rdr.ReadString('\n')
        arr := strings.Split(str, " ")
        A, _ = strconv.Atoi(arr[0])
        B, _ = strconv.Atoi(arr[1])
        D, _ = strconv.Atoi(strings.TrimSpace(arr[2]))
		E[A-1] = append(E[A-1], edge{B-1,D})
		E[B-1] = append(E[B-1], edge{A-1,D})
	}
    str, _ = rdr.ReadString('\n')
    L, _ = strconv.Atoi(strings.TrimSpace(str))
	lamp = make([]bool,N)

    if L > 0 {
        str, _ := rdr.ReadString('\n')
        arr := strings.Split(str, " ")

	    for i := 0; i < L; i++ {
		    var l int
		    l, _ = strconv.Atoi(strings.TrimSpace(arr[i]))
		    lamp[l-1] = true
	    }
    }

	res, _ := rec(-1,0,(S+1)/2)
	fmt.Println(res)
}
