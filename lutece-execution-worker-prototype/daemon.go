package main

import (
	"os"
	"time"

	"github.com/opencontainers/runc/libcontainer"
)

func RunDaemon(process *libcontainer.Process, timeLimit time.Duration, processFinished chan struct{}, chOOM <-chan struct{}, errChan chan error) {
	ticker := time.NewTicker(timeLimit)
	defer ticker.Stop()
	for {
		select {
		case <-chOOM:
			errChan <- ErrOOM
			err := process.Signal(os.Kill)
			if err != nil {
				panic(err)
			}
			return
		case <-ticker.C:
			errChan <- ErrTLE
			err := process.Signal(os.Kill)
			if err != nil {
				panic(err)
			}
			return
		case <-processFinished:
			errChan <- nil
			return
		}
	}
}
