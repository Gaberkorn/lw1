package main

import (
	"bufio"
	"fmt"
)

var linkedLists = make(map[string]*Node)

func isLLEmpty(ll *Node) bool {
	if ll == nil {
		fmt.Println("Error: Linked list is empty!")
		return true
	}
	return false
}

func isLinkedListNamedInvalid(name string) bool {
	ll, ok := linkedLists[name]
	if !ok || ll == nil {
		fmt.Printf("Error: Linked list '%s' doesn't exist!\n", name)
		return true
	}
	return false
}

func ExecuteLinkedListCommand(command string, tokens []string) {
	getToken := func(i int) (string, bool) {
		if i < len(tokens) {
			return tokens[i], true
		}
		return "", false
	}

	switch command {

	case "FADD_BEG":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		linkedLists[name] = &Node{Data: value, Next: linkedLists[name]}

	case "FADD_END":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		newNode := &Node{Data: value, Next: nil}
		head, exists := linkedLists[name]
		if !exists || head == nil {
			linkedLists[name] = newNode
		} else {
			current := head
			for current.Next != nil {
				current = current.Next
			}
			current.Next = newNode
		}
		fmt.Println(value)

	case "FADD_AFTER":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		newData, ok3 := getToken(2)
		if !ok1 || !ok2 || !ok3 {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		current := head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current != nil {
			newNode := &Node{Data: newData, Next: current.Next}
			current.Next = newNode
			fmt.Println(newData)
		} else {
			fmt.Println("Error: Element not found!")
		}

	case "FADD_BEFORE":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		newData, ok3 := getToken(2)
		if !ok1 || !ok2 || !ok3 {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		current := head
		var beforeCurrent *Node = nil
		for current != nil && current.Data != value {
			beforeCurrent = current
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else if current == head {
			linkedLists[name] = &Node{Data: newData, Next: head}
		} else {
			newNode := &Node{Data: newData, Next: current}
			beforeCurrent.Next = newNode
		}
		fmt.Println(newData)

	case "FDEL_BEG":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		linkedLists[name] = head.Next
		fmt.Println(head.Data)

	case "FDEL_END":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		if head.Next == nil {
			fmt.Println(head.Data)
			linkedLists[name] = nil
		} else {
			var beforeCurrent *Node = nil
			current := head
			for current.Next != nil {
				beforeCurrent = current
				current = current.Next
			}
			beforeCurrent.Next = nil
			fmt.Println(current.Data)
		}

	case "FDEL_AFTER":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		current := head
		for current != nil && current.Data != value {
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else if current.Next == nil {
			fmt.Println("Error: No element after it!")
		} else {
			toDelete := current.Next
			current.Next = toDelete.Next
			fmt.Println(toDelete.Data)
		}

	case "FDEL_BEFORE":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		current := head
		var beforeCurrent *Node = nil
		var beforeBefore *Node = nil
		for current != nil && current.Data != value {
			beforeBefore = beforeCurrent
			beforeCurrent = current
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else if current == head {
			fmt.Println("Error: No element before the head!")
		} else if beforeCurrent == head {
			linkedLists[name] = current
			fmt.Println(beforeCurrent.Data)
		} else {
			beforeBefore.Next = current
			fmt.Println(beforeCurrent.Data)
		}

	case "FDEL_INT":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		current := head
		var beforeCurrent *Node = nil
		for current != nil && current.Data != value {
			beforeCurrent = current
			current = current.Next
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else {
			if beforeCurrent == nil {
				linkedLists[name] = head.Next
			} else if current.Next == nil {
				beforeCurrent.Next = nil
			} else {
				beforeCurrent.Next = current.Next
			}
			fmt.Println(current.Data)
		}

	case "FGET":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		if isLLEmpty(head) {
			return
		}
		posCnt := 0
		current := head
		for current != nil && current.Data != value {
			current = current.Next
			posCnt++
		}
		if current == nil {
			fmt.Println("Error: Element not found!")
		} else {
			fmt.Println(posCnt)
		}

	case "FPRINT":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		head := linkedLists[name]
		current := head
		for current != nil {
			fmt.Printf("%s ", current.Data)
			current = current.Next
		}
		fmt.Println()

	case "FGET_BEG":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		fmt.Println(linkedLists[name].Data)

	case "FGET_END":
		name, ok := getToken(0)
		if !ok {
			return
		}
		if isLinkedListNamedInvalid(name) {
			return
		}
		current := linkedLists[name]
		for current.Next != nil {
			current = current.Next
		}
		fmt.Println(current.Data)
	}
}

func LoadLinkedListFromTokens(name string, tokens []string) {
	var head *Node = nil
	var tail *Node = nil
	for _, token := range tokens {
		newNode := &Node{Data: token, Next: nil}
		if head == nil {
			head = newNode
			tail = newNode
		} else {
			tail.Next = newNode
			tail = newNode
		}
	}
	linkedLists[name] = head
}

func SaveLinkedListsToWriter(w *bufio.Writer) {
	for name, ll := range linkedLists {
		if ll == nil {
			continue
		}
		fmt.Fprintf(w, "[LINKEDLIST:%s] ", name)
		current := ll
		for current != nil {
			fmt.Fprintf(w, "%s ", current.Data)
			current = current.Next
		}
		fmt.Fprintln(w)
	}
}
