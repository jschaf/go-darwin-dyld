# go-darwin-dyld

This repo reproduces a bug executing when executing a binary with Go
`exec.Command` on macOS using with `DYLD_INSERT_LIBRARIES`. The binary
segfaults.

### What should happen: run via shell

When executing a binary with `DYLD_INSERT_LIBRARIES` set, the binary should
run normally.

Notably, running the same binary using the shell doesn't segfault.

```shell
make run_shell # runs file_ops.c

# Output:
# !!! init dyld_inserted library
# successfully wrote tmp file: $TMPDIR/open_a
```

### What actually happens: run via Go exec.Command

```shell
make run_go # runs main.go

# Output:
# err: signal: segmentation fault
```

The bug is related to `DYLD_INSERT_LIBRARIES`. To run `exec.Command` without the
env var set, run:

```shell
SKIP_DYLD=1 make run_go

# Output:
# running  /opt/p/go-darwin-dyld/file_ops
# output: successfully wrote tmp file: $TMPDIR/open_a
```
