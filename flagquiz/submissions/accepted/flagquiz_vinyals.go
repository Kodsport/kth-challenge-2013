/* This is an example solution to the "Flag Quiz" problem from KTH Challenge 2013, held on April
 * 21, 2013.
 *
 * The solution is provided as-is, is not documented, and may be generally difficult to read.
 *
 * This work by KTH CSC (http://www.csc.kth.se/) is licensed under a Creative Commons
 * Attribution-Share Alike 2.5 Sweden License
 * (http://creativecommons.org/licenses/by-sa/2.5/se/deed.en).  You are free to redistribute it as
 * you like as long as this license information is not removed.
 */
//Solution by Marc Vinyals
package main

import (
       "fmt"
       "bufio"
       "os"
       "encoding/csv"
       "strings"
)

func max(a int, b int) (int) {
    if a<b {
        return b
    }
    return a
}

func main() {
    in := bufio.NewReader(os.Stdin)
    in.ReadString('\n')
    in.ReadString('\n')
    csvin := csv.NewReader(in)
    flags,_ := csvin.ReadAll()
    score := make([]int,len(flags))
    for t,f := range flags {
    	score[t] = 0
     	for _,g := range flags {
	    scorefg := 0
	    for i := range f {
	    	if f[i] != g[i] {
		    scorefg++
		}
	    }
	    score[t] = max(score[t],scorefg)
	}
    }
    scoremin := score[0]
    for _,s := range score {
        if s < scoremin {
	    scoremin = s
	}
    }
    for i,s := range score {
    	if s == scoremin {
	   fmt.Println(strings.Join(flags[i],","))
	}
    }
}
