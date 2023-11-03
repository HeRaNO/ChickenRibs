package main

import (
	"bytes"
	"crypto/tls"
	"encoding/csv"
	"flag"
	"fmt"
	"html/template"
	"log"
	"net/smtp"
	"os"
	"sync"

	"github.com/jordan-wright/email"
)

func makeAccountEmail(tmpl *template.Template, name *string, account *string, password *string) []byte {
	content := new(bytes.Buffer)
	tmpl.Execute(content, struct {
		Name     string
		Account  string
		Password string
	}{
		Name:     *name,
		Account:  *account,
		Password: *password,
	})
	return content.Bytes()
}

func sendEmail(emailRecv *string, content []byte) error {
	e := &email.Email{
		To:      []string{*emailRecv},
		From:    emailFrom,
		Subject: subject,
		HTML:    content,
	}

	auth := smtp.PlainAuth("", emailAddr, emailPassword, smtpAddr)
	return e.SendWithTLS(smtpHost, auth, &tls.Config{ServerName: smtpAddr})
}

func main() {
	dbFilePath := flag.String("f", "./data.csv", "the path of data file")
	flag.Parse()

	tmpl, err := template.ParseFiles("./email-account.tmpl")
	if err != nil {
		log.Fatalf("cannot parse email template file, err: %s\n", err.Error())
	}

	dbFile, err := os.Open(*dbFilePath)
	if err != nil {
		log.Fatalf("cannot open data file, err: %s\n", err.Error())
	}
	db := csv.NewReader(dbFile)
	rec, err := db.ReadAll()
	if err != nil {
		log.Fatalf("cannot read data file, err: %s\n", err.Error())
	}

	failed := sync.Map{}
	wg := sync.WaitGroup{}
	for _, usr := range rec {
		wg.Add(1)
		go func(usr []string) {
			defer wg.Done()
			content := makeAccountEmail(tmpl, &usr[1], &usr[2], &usr[3])
			recv := fmt.Sprintf("%s@std.uestc.edu.cn", usr[0])
			err := sendEmail(&recv, content)
			if err != nil {
				log.Printf("send email error, student id: %s, err: %s\n", usr[0], err.Error())
				failed.Store(usr[0], true)
			} else {
				log.Printf("send email ok, student id: %s\n", usr[0])
			}
		}(usr)
	}
	wg.Wait()

	failedIDs := make([]string, 0)
	failed.Range(func(key, value interface{}) bool {
		failedIDs = append(failedIDs, key.(string))
		return true
	})

	log.Printf("send email finished. failed student id: %+v\n", failedIDs)
}
