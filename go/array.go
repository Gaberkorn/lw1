package main

import (
	"bufio"
	"fmt"
	"strconv"
	"strings"
)

type Array struct {
	Data     []string
	Capacity int
	Size     int
}

func NewArray(capacity int) *Array {
	return &Array{
		Data:     make([]string, capacity),
		Capacity: capacity,
		Size:     0,
	}
}

func (a *Array) IncreaseSize() {
	newCap := a.Size * 2
	if newCap == 0 {
		newCap = 1
	}
	bigger := make([]string, newCap)
	copy(bigger, a.Data[:a.Size])
	a.Data = bigger
	a.Capacity = newCap
}

var arrays = make(map[string]*Array)

func isArrayNamedInvalid(name string) bool {
	arr, ok := arrays[name]
	if !ok || arr == nil {
		fmt.Printf("Error: Array '%s' doesn't exist!\n", name)
		return true
	}
	return false
}

func ExecuteArrayCommand(command string, tokens []string) {
	getToken := func(i int) (string, bool) {
		if i < len(tokens) {
			return tokens[i], true
		}
		return "", false
	}

	switch command {
	case "MINIT":
		name, ok1 := getToken(0)
		sizeStr, ok2 := getToken(1)
		if !ok1 || !ok2 {
			fmt.Println("Error: Invalid command format! Usage: MINIT <name> <size>")
			return
		}
		size, err := strconv.Atoi(sizeStr)
		if err != nil || size <= 0 || name == "" {
			fmt.Println("Error: Invalid command format! Usage: MINIT <name> <size>")
			return
		}
		if _, exists := arrays[name]; exists {
			fmt.Printf("Error: Array '%s' already exists!\n", name)
			return
		}
		arrays[name] = NewArray(size)
		fmt.Printf("Array '%s' successfully created!\n", name)

	case "MPUSH":
		name, ok1 := getToken(0)
		value, ok2 := getToken(1)
		if !ok1 || !ok2 || isArrayNamedInvalid(name) {
			return
		}
		arr := arrays[name]
		if arr.Size == arr.Capacity {
			arr.IncreaseSize()
		}
		arr.Data[arr.Size] = value
		arr.Size++
		fmt.Println(value)

	case "MINSERT":
		name, ok1 := getToken(0)
		idxStr, ok2 := getToken(1)
		value, ok3 := getToken(2)
		if !ok1 || !ok2 || !ok3 || isArrayNamedInvalid(name) {
			return
		}
		index, err := strconv.Atoi(idxStr)
		if err != nil {
			return
		}
		arr := arrays[name]
		if index < 0 || index > arr.Size {
			fmt.Println("Error: Index is out of bounds!")
			return
		}
		if arr.Size == arr.Capacity {
			arr.IncreaseSize()
		}
		copy(arr.Data[index+1:], arr.Data[index:arr.Size])
		arr.Data[index] = value
		arr.Size++
		fmt.Println(value)

	case "MGET":
		name, ok1 := getToken(0)
		idxStr, ok2 := getToken(1)
		if !ok1 || !ok2 || isArrayNamedInvalid(name) {
			return
		}
		index, err := strconv.Atoi(idxStr)
		if err != nil {
			return
		}
		arr := arrays[name]
		if index < 0 || index >= arr.Size {
			fmt.Println("Error: Index is out of bounds!")
			return
		}
		fmt.Println(arr.Data[index])

	case "MDEL":
		name, ok1 := getToken(0)
		idxStr, ok2 := getToken(1)
		if !ok1 || !ok2 || isArrayNamedInvalid(name) {
			return
		}
		index, err := strconv.Atoi(idxStr)
		if err != nil {
			return
		}
		arr := arrays[name]
		if index < 0 || index >= arr.Size {
			fmt.Println("Error: Index is out of bounds!")
			return
		}
		copy(arr.Data[index:], arr.Data[index+1:arr.Size])
		arr.Size--

	case "MREPLACE":
		name, ok1 := getToken(0)
		idxStr, ok2 := getToken(1)
		value, ok3 := getToken(2)
		if !ok1 || !ok2 || !ok3 || isArrayNamedInvalid(name) {
			return
		}
		index, err := strconv.Atoi(idxStr)
		if err != nil {
			return
		}
		arr := arrays[name]
		if index < 0 || index >= arr.Size {
			fmt.Println("Error: Index is out of bounds!")
			return
		}
		arr.Data[index] = value
		fmt.Println("Replacement successful!")

	case "MLENGTH":
		name, ok := getToken(0)
		if !ok || isArrayNamedInvalid(name) {
			return
		}
		arr := arrays[name]
		fmt.Printf("Current array's size: %d.\nArray's capacity: %d.\n", arr.Size, arr.Capacity)

	case "MPRINT":
		name, ok := getToken(0)
		if !ok || isArrayNamedInvalid(name) {
			return
		}
		arr := arrays[name]
		for i := 0; i < arr.Size; i++ {
			fmt.Printf("%s ", arr.Data[i])
		}
		fmt.Println()
	}
}

func ParseQuery(query string) (string, []string) {
	fields := strings.Fields(query)
	if len(fields) == 0 {
		return "", nil
	}
	return fields[0], fields[1:]
}

func LoadArrayFromTokens(name string, tokens []string) {
	if len(tokens) == 0 {
		return
	}
	emptySlot := "#"
	arr := NewArray(len(tokens))
	for _, token := range tokens {
		if token == emptySlot {
			break
		}
		arr.Data[arr.Size] = token
		arr.Size++
	}
	arrays[name] = arr
}

func SaveArraysToWriter(w *bufio.Writer) {
	for name, arr := range arrays {
		fmt.Fprintf(w, "[ARRAY:%s] ", name)
		for i := 0; i < arr.Size; i++ {
			fmt.Fprintf(w, "%s ", arr.Data[i])
		}
		for i := 0; i < arr.Capacity-arr.Size; i++ {
			fmt.Fprint(w, "# ")
		}
		fmt.Fprintln(w)
	}
}
