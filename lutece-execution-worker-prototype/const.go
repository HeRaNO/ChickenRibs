package main

import "errors"

var ErrTLE = errors.New("TLE")
var ErrOOM = errors.New("OOM")

const FolderNameLen = 20
