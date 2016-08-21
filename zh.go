package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strings"
	"syscall"
)

var BUILTINS = map[string]func([]string){
	"cd": func(args []string) {
		if len(args) > 1 {
			os.Chdir(args[1])
		}
	},
	"exit": func(args []string) {
		os.Exit(0)
	},
}

func GetCmd() string {
	// Scan users input
	scan := bufio.NewScanner(os.Stdin)
	scan.Scan()
	return scan.Text()
}

func RunCmd(args []string) {
	// Check builtin commands
	if run, ok := BUILTINS[args[0]]; ok {
		// Run builtin command
		run(args)
		return
	}

	// List stdin, stdout, and stderr file descriptors
	files := []uintptr{uintptr(syscall.Stdin), uintptr(syscall.Stdout), uintptr(syscall.Stderr)}
	// Set process attributes
	proc := syscall.ProcAttr{Files: files}
	// Find the full path of the program
	prog, _ := exec.LookPath(args[0])
	// Fork and exec command
	pid, _ := syscall.ForkExec(prog, args, &proc)
	syscall.Wait4(pid, nil, 0, nil)
}

func main() {
	for {
		// Print prompt
		fmt.Printf("ζ ")

		// Get command
		cmd := GetCmd()
		// Parse command
		args := strings.Split(cmd, " ")

		if len(args) > 0 {
			// Run command
			RunCmd(args)
		}
	}
}
