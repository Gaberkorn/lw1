package main

import (
	"bufio"
	"fmt"
)

type Stack struct {
	Head *Node
}

var stacks = make(map[string]*Stack)

func isStackEmpty(stack *Stack) bool {
	if stack == nil || stack.Head == nil {
		fmt.Println("Error: Stack is empty!")
		return true
	}
	return false
}

func isStackNamedInvalid(name string) bool {
	st, ok := stacks[name]
	if !ok || st == nil {
		fmt.Printf("Error: Stack '%s' doesn't exist!\n", name)
		return true
	}
	return false
}

func getOrCreateStack(name string) *Stack {
	st, ok := stacks[name]
	if !ok || st == nil {
		st = &Stack{Head: nil}
		stacks[name] = st
	}
	return st
}

func ExecuteStackCommand(command string, tokens []string) {
	getToken := func(i int) (string, bool) {
		if i < len(tokens) {
			return tokens[i], true
		}
		return "", false
	}

	switch command {

	case "SPUSH":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		myStack := getOrCreateStack(name)
		newNode := &Node{Data: value, Next: myStack.Head}
		myStack.Head = newNode
		fmt.Println(value)

	case "SPOP":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isStackNamedInvalid(name) {
			return
		}
		myStack := stacks[name]
		if isStackEmpty(myStack) {
			return
		}
		newHead := myStack.Head.Next
		fmt.Println(myStack.Head.Data)
		myStack.Head = newHead

	case "STOP":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isStackNamedInvalid(name) {
			return
		}
		myStack := stacks[name]
		if isStackEmpty(myStack) {
			return
		}
		fmt.Println(myStack.Head.Data)

	case "SPRINT":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isStackNamedInvalid(name) {
			return
		}
		current := stacks[name].Head
		for current != nil {
			fmt.Printf("%s ", current.Data)
			current = current.Next
		}
		fmt.Println()
	}
}

func LoadStackFromTokens(name string, tokens []string) {
	myStack := &Stack{Head: nil}
	for _, token := range tokens {
		newNode := &Node{Data: token, Next: myStack.Head}
		myStack.Head = newNode
	}
	stacks[name] = myStack
}

func SaveStacksToWriter(w *bufio.Writer) {
	for name, st := range stacks {
		if st == nil || st.Head == nil {
			continue
		}
		fmt.Fprintf(w, "[STACK:%s] ", name)
		current := st.Head
		for current != nil {
			fmt.Fprintf(w, "%s ", current.Data)
			current = current.Next
		}
		fmt.Fprintln(w)
	}
}
