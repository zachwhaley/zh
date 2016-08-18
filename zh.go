package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strings"
	"syscall"
)

func GetCmd() string {
	// Scan users input
	scan := bufio.NewScanner(os.Stdin)
	scan.Scan()
	return scan.Text()
}

func RunCmd(cmd string) {
	// List stdin, stdout, and stderr file descriptors
	files := []uintptr{uintptr(syscall.Stdin), uintptr(syscall.Stdout), uintptr(syscall.Stderr)}
	// Set process attributes
	proc := syscall.ProcAttr{Files: files}
	// Split command into slice of arguments
	args := strings.Split(cmd, " ")
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
		// Run command
		RunCmd(cmd)
	}
}
