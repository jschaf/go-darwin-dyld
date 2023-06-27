package main

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strings"
)

func main() {
	skipDyld := os.Getenv("SKIP_DYLD") != ""
	fmt.Printf("main.go start: skipDyld=%v\n", skipDyld)

	wd, err := os.Getwd()
	if err != nil {
		fmt.Printf("err: %v\n", err)
		os.Exit(1)
	}

	fileOpsExec := filepath.Join(wd, "file_ops")
	fslogPath := filepath.Join(wd, "fslog.dylib")

	cmd := exec.Command(fileOpsExec)
	if !skipDyld {
		cmd.Env = append(cmd.Env, "DYLD_INSERT_LIBRARIES="+fslogPath)
	}
	fmt.Printf("running %s %s\n", strings.Join(cmd.Env, " "), cmd.String())
	output, err := cmd.Output()
	if err != nil {
		fmt.Printf("err: %v\noutput: %s\n", err, string(output))
		os.Exit(1)
	}
	fmt.Printf("output:\n%s\n", string(output))
}
