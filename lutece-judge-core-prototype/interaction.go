package main

import (
	"log"
	"os"

	"github.com/opencontainers/runc/libcontainer"
	"github.com/opencontainers/runc/libcontainer/configs"
)

func Interaction(factory libcontainer.Factory, config *configs.Config, configGrader *configs.Config) {
	reader1, writer1, err := os.Pipe()
	if err != nil {
		panic(err)
	}
	reader2, writer2, err := os.Pipe()
	if err != nil {
		panic(err)
	}
	usrErrFile, err := os.OpenFile("usrErrFile", os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		panic(err)
	}
	graderErrFile, err := os.OpenFile("graderErrFile", os.O_CREATE|os.O_RDWR, 0644)
	if err != nil {
		panic(err)
	}
	processUser := &libcontainer.Process{
		Args:   []string{"./interaction"},
		Env:    []string{"PATH=/bin"},
		User:   "test",
		Cwd:    "/judge-test",
		Stdin:  reader1,
		Stdout: writer2,
		Stderr: usrErrFile,
		Init:   true,
	}
	processGrader := &libcontainer.Process{
		Args:   []string{"./grader", "input.txt", "output"},
		Env:    []string{"PATH=/bin"},
		User:   "test",
		Cwd:    "/judge-test",
		Stdin:  reader2,
		Stdout: writer1,
		Stderr: graderErrFile,
		Init:   true,
	}

	usrContainer, err := factory.Create("usr-container", config)
	if err != nil {
		log.Fatal(err)
		return
	}
	defer usrContainer.Destroy()
	graderContainer, err := factory.Create("grader-container", configGrader)
	if err != nil {
		log.Fatal(err)
		return
	}
	defer graderContainer.Destroy()

	var userP *os.ProcessState

	err = graderContainer.Run(processGrader)
	if err != nil {
		log.Fatal(err)
		return
	}

	go func() {
		err = usrContainer.Run(processUser)
		if err != nil {
			log.Fatal(err)
			return
		}
		userP, err = processUser.Wait()
		if err != nil {
			log.Println(err)
		}
	}()

	graderP, err := processGrader.Wait()
	if err != nil {
		log.Println(err)
	}

	stat, err := usrContainer.Stats()
	if err != nil {
		panic(err)
	}

	processStat := stat.CgroupStats
	cpuStat := processStat.CpuStats
	memoryStat := processStat.MemoryStats
	log.Printf("cpuStat: %+v", cpuStat)
	log.Printf("memoryStat: %+v", memoryStat)

	log.Println(userP.UserTime().Microseconds())
	log.Println(userP.SystemTime().Microseconds())
	log.Printf("%+v", userP.SysUsage())

	log.Println("----------")

	log.Println(graderP.UserTime().Microseconds())
	log.Println(graderP.SystemTime().Microseconds())
	log.Printf("%+v", graderP.SysUsage())
}
