package main

import (
	"log"
	"os"
	"time"

	"github.com/opencontainers/runc/libcontainer"
	"github.com/opencontainers/runc/libcontainer/configs"
)

func Batch(factory libcontainer.Factory, config *configs.Config) {
	timeLimit := 1000 + 200
	inputFile, err := os.Open("input")
	if err != nil {
		panic(err)
	}
	outputFile, err := os.OpenFile("user_out", os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		panic(err)
	}
	errFile, err := os.OpenFile("errFile", os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		panic(err)
	}
	process := &libcontainer.Process{
		Args:   []string{"./apb"},
		Env:    []string{"PATH=/bin"},
		Cwd:    "/judge-test",
		User:   "test",
		Stdin:  inputFile,
		Stdout: outputFile,
		Stderr: errFile,
		Init:   true,
		/*Stdin:  os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
		*/
	}

	container, err := factory.Create("container-id", config)
	if err != nil {
		log.Fatal(err)
		return
	}
	defer container.Destroy()

	err = container.Run(process)
	if err != nil {
		log.Fatal(err)
		return
	}

	processFinished := make(chan struct{})
	chMLE, err := container.NotifyOOM()
	if err != nil {
		panic(err)
	}

	go func() {
		ticker := time.NewTicker(time.Duration(timeLimit) * time.Millisecond)
		defer ticker.Stop()
		for {
			select {
			case <-chMLE:
				err := process.Signal(os.Kill)
				if err != nil {
					panic(err)
				}
				log.Println("MLE!!!")
			case <-ticker.C:
				err := process.Signal(os.Kill)
				if err != nil {
					panic(err)
				}
				log.Println("TLE!!!")
			case <-processFinished:
				return
			}
		}
	}()

	p, err := process.Wait()
	if err != nil {
		log.Println(err)
	}
	processFinished <- struct{}{} // Should always use this to kill the daemon goroutine

	stat, err := container.Stats()
	if err != nil {
		panic(err)
	}

	processStat := stat.CgroupStats
	cpuStat := processStat.CpuStats
	memoryStat := processStat.MemoryStats
	log.Printf("cpuStat: %+v", cpuStat)
	log.Printf("memoryStat: %+v", memoryStat)

	log.Println(p.UserTime().Microseconds())
	log.Println(p.SystemTime().Microseconds())
	log.Printf("%+v", p.SysUsage())
}
