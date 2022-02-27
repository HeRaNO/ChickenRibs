package main

import (
	"sync"

	jsoniter "github.com/json-iterator/go"
	"github.com/rabbitmq/amqp091-go"
)

func prepareFiles() error {
	// MinIOClient.FGetObject(context.Background())
	return nil
}

func prepareContainer() error {
	return nil
}

func HandleReq(req amqp091.Delivery) error {
	execReq := ExecRequest{}
	err := jsoniter.Unmarshal(req.Body, &execReq)
	if err != nil {
		return err
	}

	for _, stage := range execReq.Phases {
		err := HandlePhase(stage)
		if err != nil {
			return err
		}
	}
	return nil
}

func HandlePhase(phase Phase) error {
	wg := sync.WaitGroup{}
	oneErr := OneError{}
	wg.Add(1)
	go func() {
		defer wg.Done()
		err := prepareFiles()
		if err != nil {
			oneErr.Add(err)
		}
	}()
	wg.Add(1)
	go func() {
		defer wg.Done()
		err := prepareContainer()
		if err != nil {
			oneErr.Add(err)
		}
	}()
	folderPath, err := Mkdir(conf.Rootfs.RootfsPath)
	if err != nil {
		return err
	}
	wg.Wait()
	if oneErr.err != nil {
		return oneErr.err
	}
	executeSingle(nil)
	return nil
}
