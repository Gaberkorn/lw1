package main

import (
	"bufio"
	"fmt"
)

type DLLNode struct {
	Data string
	Next *DLLNode
	Back *DLLNode
}

type DLL struct {
	Head *DLLNode
	Tail *DLLNode
}

var dLinkedLists = make(map[string]*DLL)

func isDLLEmpty(ll *DLL) bool {
	if ll == nil || ll.Head == nil {
		fmt.Println("Error: Linked list is empty!")
		return true
	}
	return false
}

func isDLLNamedInvalid(name string) bool {
	ll, ok := dLinkedLists[name]
	if !ok || ll == nil {
		fmt.Printf("Error: Double Linked list '%s' doesn't exist!\n", name)
		return true
	}
	return false
}

func getOrCreateDLL(name string) *DLL {
	ll, ok := dLinkedLists[name]
	if !ok || ll == nil {
		ll = &DLL{Head: nil, Tail: nil}
		dLinkedLists[name] = ll
	}
	return ll
}

func ExecuteDLinkedListCommand(command string, tokens []string) {
	getToken := func(i int) (string, bool) {
		if i < len(tokens) {
			return tokens[i], true
		}
		return "", false
	}

	switch command {

	case "LADD_BEG":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		myList := getOrCreateDLL(name)
		newNode := &DLLNode{Data: value, Next: myList.Head, Back: nil}
		if myList.Head == nil {
			myList.Head = newNode
			myList.Tail = newNode
		} else {
			myList.Head.Back = newNode
			myList.Head = newNode
		}
		fmt.Println(value)

	case "LADD_END":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		myList := getOrCreateDLL(name)
		newNode := &DLLNode{Data: value, Next: nil, Back: myList.Tail}
		if myList.Head == nil {
			myList.Head = newNode
			myList.Tail = newNode
		} else {
			myList.Tail.Next = newNode
			myList.Tail = newNode
		}
		fmt.Println(value)

	case "LADD_AFTER":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		newData, ok3 := getToken(2)
		if !ok1 || !ok2 || !ok3 {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		current := myList.Head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current != nil {
			newNode := &DLLNode{Data: newData, Next: current.Next, Back: current}
			if current.Next != nil {
				current.Next.Back = newNode
			} else {
				myList.Tail = newNode
			}
			current.Next = newNode
		} else {
			fmt.Println("Error: Element not found!")
		}
		fmt.Println(newData)

	case "LADD_BEFORE":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		newData, ok3 := getToken(2)
		if !ok1 || !ok2 || !ok3 {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		current := myList.Head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else if current == myList.Head {
			newNode := &DLLNode{Data: newData, Next: myList.Head, Back: nil}
			myList.Head.Back = newNode
			myList.Head = newNode
		} else {
			newNode := &DLLNode{Data: newData, Next: current, Back: current.Back}
			current.Back.Next = newNode
			current.Back = newNode
		}
		fmt.Println(newData)

	case "LDEL_BEG":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		deleteNode := myList.Head
		myList.Head = myList.Head.Next
		if myList.Head == nil {
			myList.Tail = nil
		} else {
			myList.Head.Back = nil
		}
		fmt.Println(deleteNode.Data)

	case "LDEL_END":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		deleteNode := myList.Tail
		myList.Tail = myList.Tail.Back
		if myList.Tail == nil {
			myList.Head = nil
		} else {
			myList.Tail.Next = nil
		}
		fmt.Println(deleteNode.Data)

	case "LDEL_AFTER":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		current := myList.Head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else if current.Next == nil {
			fmt.Println("Error: No element after it!!")
		} else {
			deleteNode := current.Next
			current.Next = deleteNode.Next
			if deleteNode.Next != nil {
				deleteNode.Next.Back = current
			} else {
				myList.Tail = current
			}
			fmt.Println(deleteNode.Data)
		}

	case "LDEL_BEFORE":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		current := myList.Head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else if current == myList.Head {
			fmt.Println("Error: No element before the head!")
		} else if current.Back == myList.Head {
			deleteNode := myList.Head
			myList.Head = myList.Head.Next
			myList.Head.Back = nil
			fmt.Println(deleteNode.Data)
		} else {
			deleteNode := current.Back
			deleteNode.Back.Next = current
			current.Back = deleteNode.Back
			fmt.Println(deleteNode.Data)
		}

	case "LDEL_INT":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		current := myList.Head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else {
			if current.Back != nil {
				current.Back.Next = current.Next
			} else {
				myList.Head = current.Next
			}
			if current.Next != nil {
				current.Next.Back = current.Back
			} else {
				myList.Tail = current.Back
			}
			fmt.Println(current.Data)
		}

	case "LGET":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		if isDLLEmpty(myList) {
			return
		}
		posCnt := 0
		current := myList.Head
		for current != nil && current.Data != value {
			current = current.Next
			posCnt++
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else {
			fmt.Println(posCnt)
		}

	case "LPRINT":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		myList := dLinkedLists[name]
		current := myList.Head
		for current != nil {
			fmt.Printf("%s ", current.Data)
			current = current.Next
		}
		fmt.Println()

	case "LGET_BEG":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		fmt.Println(dLinkedLists[name].Head.Data)

	case "LGET_END":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isDLLNamedInvalid(name) {
			return
		}
		fmt.Println(dLinkedLists[name].Tail.Data)
	}
}

func LoadDLinkedListFromTokens(name string, tokens []string) {
	myList := &DLL{Head: nil, Tail: nil}
	for _, token := range tokens {
		newNode := &DLLNode{Data: token, Next: nil, Back: myList.Tail}
		if myList.Head == nil {
			myList.Head = newNode
			myList.Tail = newNode
		} else {
			myList.Tail.Next = newNode
			myList.Tail = newNode
		}
	}
	dLinkedLists[name] = myList
}

func SaveDLinkedListsToWriter(w *bufio.Writer) {
	for name, dll := range dLinkedLists {
		if dll == nil || dll.Head == nil {
			continue
		}
		fmt.Fprintf(w, "[DOUBLELINKEDLIST:%s] ", name)
		current := dll.Head
		for current != nil {
			fmt.Fprintf(w, "%s ", current.Data)
			current = current.Next
		}
		fmt.Fprintln(w)
	}
}
