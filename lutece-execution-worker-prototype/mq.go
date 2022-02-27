package main

import (
	"fmt"
	"log"

	amqp "github.com/rabbitmq/amqp091-go"
)

func InitMQ() <-chan amqp.Delivery {
	amqpUrl := fmt.Sprintf("amqp://%s:%s@%s:%d/", conf.MQ.UserName, conf.MQ.Password,
		conf.MQ.IP, conf.MQ.Port)
	conn, err := amqp.Dial(amqpUrl)
	if err != nil {
		log.Println("[FATAL] Init message queue failed: dial failed")
		panic(err)
	}

	ch, err := conn.Channel()
	if err != nil {
		log.Println("[FATAL] Init message queue failed: init channel failed")
		panic(err)
	}
	q, err := ch.QueueDeclare("", true, false, true, false, nil)
	if err != nil {
		log.Println("[FATAL] Init message queue failed: declare queue failed")
		panic(err)
	}
	err = ch.Qos(1, 0, false)
	if err != nil {
		log.Println("[FATAL] Init message queue failed: set Qos failed")
		panic(err)
	}
	msgs, err := ch.Consume(q.Name, "", false, false, false, false, nil)
	if err != nil {
		log.Println("[FATAL] Init message queue failed: failed to register a consumer")
		panic(err)
	}
	log.Println("[INFO] Init message queue successfully")
	return msgs
}
