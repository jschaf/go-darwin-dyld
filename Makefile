
run_go: build_file_ops build_fslog_dylib main.go
	SKIP_DYLD=$(skip_dyld) go run ./main.go

run_shell: build_file_ops build_fslog_dylib
	DYLD_INSERT_LIBRARIES=./fslog.dylib ./file_ops

build_file_ops: file_ops.c
	clang -o file_ops file_ops.c

build_fslog_dylib: fslog.c
	clang -dynamiclib -o fslog.dylib fslog.c