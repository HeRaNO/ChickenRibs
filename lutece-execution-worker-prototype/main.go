package main

import (
	"flag"
	"log"
)

func main() {
	initConfigFile := flag.String("c", "./config.yaml", "the path of configure file")

	InitConfig(initConfigFile)
	msgQ := InitMQ()
	InitContainer()
	InitMinIO()
	for req := range msgQ {
		HandleReq(req)
	}

	log.Panicln("[FATAL] Why execute this line???")
}
