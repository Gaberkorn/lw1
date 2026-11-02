package main

import (
	"bufio"
	"fmt"
)

type Queue struct {
	Head *Node
	Tail *Node
}

var queues = make(map[string]*Queue)

func isQueueEmpty(queue *Queue) bool {
	if queue == nil || queue.Head == nil {
		fmt.Println("Error: Queue is empty!")
		return true
	}
	return false
}

func isQueueNamedInvalid(name string) bool {
	q, ok := queues[name]
	if !ok || q == nil {
		fmt.Printf("Error: Queue '%s' doesn't exist!\n", name)
		return true
	}
	return false
}

func getOrCreateQueue(name string) *Queue {
	q, ok := queues[name]
	if !ok || q == nil {
		q = &Queue{Head: nil, Tail: nil}
		queues[name] = q
	}
	return q
}

func ExecuteQueueCommand(command string, tokens []string) {
	getToken := func(i int) (string, bool) {
		if i < len(tokens) {
			return tokens[i], true
		}
		return "", false
	}

	switch command {

	case "QPUSH":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		myQueue := getOrCreateQueue(name)
		newNode := &Node{Data: value, Next: nil}
		if myQueue.Head == nil {
			myQueue.Head = newNode
		} else {
			myQueue.Tail.Next = newNode
		}
		myQueue.Tail = newNode
		fmt.Println(value)

	case "QPOP":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isQueueNamedInvalid(name) {
			return
		}
		myQueue := queues[name]
		if isQueueEmpty(myQueue) {
			return
		}
		deleteNode := myQueue.Head
		fmt.Println(deleteNode.Data)

		if myQueue.Head == myQueue.Tail {
			myQueue.Head = nil
			myQueue.Tail = nil
		} else {
			myQueue.Head = myQueue.Head.Next
		}

	case "QFRONT":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isQueueNamedInvalid(name) {
			return
		}
		myQueue := queues[name]
		if isQueueEmpty(myQueue) {
			return
		}
		fmt.Println(myQueue.Head.Data)

	case "QPRINT":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isQueueNamedInvalid(name) {
			return
		}
		current := queues[name].Head
		for current != nil {
			fmt.Printf("%s ", current.Data)
			current = current.Next
		}
		fmt.Println()
	}
}

func LoadQueueFromTokens(name string, tokens []string) {
	myQueue := &Queue{Head: nil, Tail: nil}
	for _, token := range tokens {
		newNode := &Node{Data: token, Next: nil}
		if myQueue.Head == nil {
			myQueue.Head = newNode
		} else {
			myQueue.Tail.Next = newNode
		}
		myQueue.Tail = newNode
	}
	queues[name] = myQueue
}

func SaveQueuesToWriter(w *bufio.Writer) {
	for name, q := range queues {
		if q == nil || q.Head == nil {
			continue
		}
		fmt.Fprintf(w, "[QUEUE:%s] ", name)
		current := q.Head
		for current != nil {
			fmt.Fprintf(w, "%s ", current.Data)
			current = current.Next
		}
		fmt.Fprintln(w)
	}
}
