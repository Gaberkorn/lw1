package main

import (
	"fmt"
	"os"
)

type Domain int

const (
	DomainUnknown Domain = iota
	DomainArray
	DomainLinkedList
	DomainDoubleLinkedList
	DomainStack
	DomainQueue
	DomainTree
)

func detectDomain(w byte) Domain {
	switch w {
	case 'M':
		return DomainArray
	case 'F':
		return DomainLinkedList
	case 'L':
		return DomainDoubleLinkedList
	case 'S':
		return DomainStack
	case 'Q':
		return DomainQueue
	default:
		return DomainUnknown
	}
}

func main() {
	var filename string
	var query string

	args := os.Args[1:]
	for i := 0; i < len(args); i++ {
		switch args[i] {
		case "--file":
			if i+1 < len(args) {
				filename = args[i+1]
				i++
			}
		case "--query":
			if i+1 < len(args) {
				query = args[i+1]
				i++
			}
		}
	}

	if filename == "" || query == "" {
		fmt.Fprintln(os.Stderr, "Usage: ./dbms --file <filename> --query '<command>'")
		os.Exit(1)
	}

	LoadFromFile(filename)

	command, tokens := ParseQuery(query)

	domain := DomainUnknown
	if len(query) > 0 {
		domain = detectDomain(query[0])
	}

	switch domain {
	case DomainArray:
		ExecuteArrayCommand(command, tokens)
	case DomainLinkedList:
		ExecuteLinkedListCommand(command, tokens)
	case DomainDoubleLinkedList:
		ExecuteDLinkedListCommand(command, tokens)
	case DomainStack:
		ExecuteStackCommand(command, tokens)
	case DomainQueue:
		ExecuteQueueCommand(command, tokens)
	default:
	}

	SaveToFile(filename)
}