package main

import (
	"fmt"
	"time"
	"math/rand"
)

func sumSig(a[] int64, n int) int64 {
	var sum int64
	sum = 0
	for i := 0; i < n; i++ {
		sum += a[i]
	}
	return sum
}

func adder(a[] int64, n int) <-chan int64 {
	out := make(chan int64)
	go func () {
		var sum int64
		sum = 0
		for i := 0; i < n; i++ {
			sum += a[i]
		}
		out <- sum
	}()
	return out
}

func sumMul(a[] int64, n int) int64 {
	var sum int64
	sum = 0
	const workerCnt = 8
	workerLen := n / workerCnt
	var chs[workerCnt] <-chan int64
	for i := 0; i < workerCnt; i++ {
		chs[i] = adder(a[i * workerLen : (i + 1) * workerLen], workerLen)
	}
	for i := 0; i < workerCnt; i++ {
		sum += <-chs[i]
	}
	return sum
}

func main() {
	var s int64
	rand.Seed(time.Now().Unix())

	const MAX = 100000000
	arr := make([]int64, MAX)

	for i := 0; i < MAX; i++ {
		arr[i] = rand.Int63n(100000000)
	}

	t1 := time.Now().UnixNano()
	s = sumSig(arr, MAX)
	t2 := time.Now().UnixNano() - t1
	fmt.Printf("Single: time: %d, sum: %d\n", t2, s)

	t1 = time.Now().UnixNano()
	s = sumMul(arr, MAX)
	t2 = time.Now().UnixNano() - t1
	fmt.Printf("Multi: time: %d, sum: %d\n", t2, s)
}