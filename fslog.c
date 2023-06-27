#include <stdio.h>

__attribute__((constructor))
void fslog_init() {
    printf("!!! init dyld_inserted library\n");
}