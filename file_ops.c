#include <sys/fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <printf.h>
#include <errno.h>

const char *path_join(char *a, char *b) {
    size_t aLen = strlen(a);
    size_t bLen = strlen(b);
    if (aLen == 0) return b;
    if (bLen == 0) return a;

    size_t newLen = aLen + bLen + 2;
    char *result = calloc(newLen, sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    strlcpy(result, a, aLen + 1);
    if (a[aLen - 1] != '/') {
        strlcat(result, "/", newLen);
    }
    if (b[0] == '/') {
        strlcat(result, b + 1, newLen);
    } else {
        strlcat(result, b, newLen);
    }
    return result;
}

int main() {
    // Write a temp file with the contents "open 1"
    char *tmpdir = getenv("TMPDIR");
    const char *openAPath = path_join(tmpdir, "open_a");
    int fd = open(openAPath, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        printf("error: open tmp %s: %s\n", openAPath, strerror(errno));
        return 1;
    }
    ssize_t n = write(fd, "open 1", 6);
    if (n < 0) {
        printf("error: write to %s: %s\n", openAPath, strerror(errno));
        return 1;
    }
    if (close(fd) < 0) {
        printf("error: close file %s: %s\n", openAPath, strerror(errno));
        return 1;
    }

    printf("successfully wrote tmp file: %s\n", openAPath);
}
