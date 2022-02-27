package main

import (
	"log"
	"os"

	"github.com/opencontainers/runc/libcontainer"
)

var Factory libcontainer.Factory

func InitContainer() {
	factory, err := libcontainer.New(conf.Rootfs.ContainerFilePath, libcontainer.InitArgs(os.Args[0], "init"))
	if err != nil {
		log.Println("[FATAL] Init container failed")
		panic(err)
	}

	Factory = factory
	log.Println("[INFO] Init container successfully")
	return
}
