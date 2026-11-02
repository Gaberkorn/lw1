package main

import (
	"bufio"
	"os"
	"strings"
)

func LoadFromFile(filename string) {
	file, err := os.Open(filename)
	if err != nil {
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	scanner.Buffer(make([]byte, 0, 64*1024), 1024*1024)

	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			continue
		}

		fields := strings.Fields(line)
		if len(fields) == 0 {
			continue
		}
		header := fields[0]
		tokens := fields[1:]

		if len(header) < 2 || header[0] != '[' || header[len(header)-1] != ']' {
			continue
		}
		cleanHeader := header[1 : len(header)-1]

		colonPos := strings.Index(cleanHeader, ":")
		if colonPos == -1 {
			continue
		}
		typ := cleanHeader[:colonPos]
		name := cleanHeader[colonPos+1:]

		switch typ {
		case "ARRAY":
			LoadArrayFromTokens(name, tokens)
		case "LINKEDLIST":
			LoadLinkedListFromTokens(name, tokens)
		case "DOUBLELINKEDLIST":
			LoadDLinkedListFromTokens(name, tokens)
		case "STACK":
			LoadStackFromTokens(name, tokens)
		case "QUEUE":
			LoadQueueFromTokens(name, tokens)
		}
	}
}

func SaveToFile(filename string) {
	file, err := os.Create(filename)
	if err != nil {
		return
	}
	defer file.Close()

	w := bufio.NewWriter(file)
	defer w.Flush()

	SaveArraysToWriter(w)
	SaveLinkedListsToWriter(w)
	SaveDLinkedListsToWriter(w)
	SaveStacksToWriter(w)
	SaveQueuesToWriter(w)
}