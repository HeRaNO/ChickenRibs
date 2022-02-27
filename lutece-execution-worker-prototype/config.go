package main

import (
	"io/ioutil"
	"log"

	"gopkg.in/yaml.v2"
)

var conf *Configure

type Configure struct {
	Rootfs        RootfsConfig `yaml:"rootfs"`
	MQ            MQConfig     `yaml:"mq"`
	CacheFilePath string       `yaml:"cacheFilesPath"`
	MinIO         MinIOConfig  `yaml:"minio"`
}

type RootfsConfig struct {
	RootfsPath        string `yaml:"rootfsPath"`
	ContainerFilePath string `yaml:"containerFilePath"`
}

type MQConfig struct {
	IP       string `yaml:"ip"`
	Port     int    `yaml:"port"`
	UserName string `yaml:"userName"`
	Password string `yaml:"password"`
}

type MinIOConfig struct {
	EndPoint        string `yaml:"endpoint"`
	AccessKeyID     string `yaml:"accessKeyID"`
	SecretAccessKey string `yaml:"secretAccessKey"`
	UseSSL          bool   `yaml:"useSSL"`
}

func InitConfig(filePath *string) {
	fileBytes, err := ioutil.ReadFile(*filePath)
	if err != nil {
		log.Println("[FAILED] read config file failed")
		panic(err)
	}
	if err = yaml.Unmarshal(fileBytes, &conf); err != nil {
		log.Println("[FAILED] unmarshal yaml file failed")
		panic(err)
	}
	log.Println("[INFO] Init config successfully")
}
