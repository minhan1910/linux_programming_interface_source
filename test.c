#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void non_blocking_io() {
    int fds[2];
    pipe(fds); // 0 - read end, 1 - write end

    int flags = fcntl(fds[0], F_GETFL, 0);
    fcntl(fds[0], F_SETFL, flags | O_NONBLOCK);

    char buffer[100];
    ssize_t n = read(fds[0], buffer, sizeof(buffer));

    if (n == -1) {
        perror("read");
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("✅ read() returned EAGAIN (non-blocking)\n");
        }
    } else {
        printf("Read %zd bytes: %.*s\n", n, (int)n, buffer);
    }
}

int file_io_blocking() {
    int fd = open("test.txt", O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[100];
    ssize_t n = read(fd, buffer, sizeof(buffer));

    if (n == -1) {
        perror("read");
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            printf("read() returned EAGAIN (non-blocking)\n");
        }
    } else {
        printf("Read %zd bytes: %.*s\n", n, (int)n, buffer);
    }

    close(fd);
    return 0;
}

int main(int argc, char const *argv[])
{
    return file_io_blocking();
}
