package main

import (
	"crypto/rand"
	"math/big"
	"os"
	"path/filepath"
	"time"
)

const sigma = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

func GetWallTimeLimit(limit int64) time.Duration {
	timeWithRedundancy := limit + 100
	return time.Duration(timeWithRedundancy) * time.Millisecond
}

// Generate a token whose length is `n`
func GenToken(n int) (string, error) {
	b := make([]byte, n)
	rng := new(big.Int).SetInt64(int64(len(sigma)))
	for i := 0; i < n; i++ {
		idx, err := rand.Int(rand.Reader, rng)
		if err != nil {
			return "", err
		}
		b[i] = sigma[idx.Int64()]
	}
	return string(b), nil
}

func Mkdir(parent string) (string, error) {
	wdName, err := GenToken(FolderNameLen)
	if err != nil {
		return "", err
	}
	wdName = filepath.Join(parent, wdName)
	err = os.Mkdir(wdName, 0644)
	if err != nil {
		return "", err
	}
	return wdName, nil
}

// Turn MiB to Byte
func MiB(x int64) int64 {
	return x << 20
}
