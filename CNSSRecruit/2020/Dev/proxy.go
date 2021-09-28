package main

import (
	"io"
	"fmt"
	"log"
	"net"
	"bytes"
	"net/url"
	"strings"
)

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)

	lis, err := net.Listen("tcp", ":8080")
	if err != nil {
		log.Panic(err)
	}

	for {
		cli, err := lis.Accept()
		if err != nil {
			log.Print(err)
		}

		go handleRequest(cli)
	}
}

func handleRequest(cli net.Conn) {
	if cli == nil {
		return
	}
	defer cli.Close()

	var packet [1024]byte
	n, err := cli.Read(packet[:])
	if err != nil {
		log.Println(err)
		return
	}

	if bytes.IndexByte(packet[:], '\n') == -1 {
		return
	}

	var method, host, address string
	fmt.Sscanf(string(packet[:bytes.IndexByte(packet[:], '\n')]), "%s%s", &method, &host)

	hostPortURL, err := url.Parse(host)
	if err != nil {
		log.Println(err)
		return
	}

	log.Println(hostPortURL.Scheme, hostPortURL.Opaque)

	if hostPortURL.Scheme == "http" {
		if strings.Index(hostPortURL.Host, ":") == -1 {
			address = hostPortURL.Host + ":80"
		} else {
			address = hostPortURL.Host
		}
	} else {
		address = hostPortURL.Scheme + ":" + hostPortURL.Opaque
	}

	log.Println(method, address)

	srv, err := net.Dial("tcp", address)
	if err != nil {
		log.Println(err)
		return
	}
	defer srv.Close()

	if method == "CONNECT" {
		fmt.Fprint(cli, "HTTP/1.1 200 Connection established\r\n\r\n")
	} else {
		log.Println("server write", method)
		srv.Write(packet[:n])
	}

	go func() {
		io.Copy(srv, cli)
	}()
	io.Copy(cli, srv)
}