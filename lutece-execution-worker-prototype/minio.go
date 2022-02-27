package main

import (
	"log"

	"github.com/minio/minio-go/v7"
	"github.com/minio/minio-go/v7/pkg/credentials"
)

var MinIOClient *minio.Client

func InitMinIO() {
	minioClient, err := minio.New(conf.MinIO.EndPoint, &minio.Options{
		Creds:  credentials.NewStaticV4(conf.MinIO.AccessKeyID, conf.MinIO.SecretAccessKey, ""),
		Secure: conf.MinIO.UseSSL,
	})
	if err != nil {
		log.Println("[FATAL] Init MinIO error")
		panic(err)
	}

	MinIOClient = minioClient
	return
}
