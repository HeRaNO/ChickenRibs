package main

import "sync"

type OneError struct {
	errOnce sync.Once
	err     error
}

func (e *OneError) Add(err error) {
	e.errOnce.Do(func() {
		e.err = err
	})
}
