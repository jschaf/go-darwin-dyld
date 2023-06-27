
run_go: file_ops fslog_dylib
	go run ./main.go

run_shell: file_ops fslog_dylib
	DYLD_INSERT_LIBRARIES=./fslog.dylib ./file_ops

file_ops: file_ops.c
	clang -o file_ops file_ops.c

fslog_dylib: fslog.c
	clang -dynamiclib -o fslog.dylib fslog.c