#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include "lib/tlpi_hdr.h"

// ./seek_io file r100000 whello-world
int main(int argc, char const *argv[])
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s file {r<Length>|R<Length>|s<Offset>|w<Str>}...", argv[0]);
    }

    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (fd == -1)
    {
        errExit("open");
    }

    for (int i = 2; i < argc; ++i)
    {
        switch (argv[i][0])
        {
        case 'r':
        case 'R': 
        {
            long int len = getLong(&argv[i][1], GN_ANY_BASE, argv[i]);

            char *buffer = malloc(len);
            if (buffer == NULL)
                errExit("malloc");

            ssize_t numRead = read(fd, buffer, len);

            for (int j = 0; j < numRead; ++j)
            {
                if (argv[i][0] == 'r')
                {
                    // print as text
                    printf("%c", isprint((unsigned char)buffer[j]) ? buffer[j] : '?');
                }
                else
                {
                    // print as hex
                    printf("%02x ", (unsigned int) buffer[j]);
                }
            }

            free(buffer);
            break;
        }

        case 'w':
        {
            ssize_t numWritten = write(fd, &argv[i][1], strlen(&argv[i][1]));
            if (numWritten == -1)
                errExit("write");
            printf("%s: Wrote %ld bytes\n", argv[i], numWritten);
            break;
        }
            

        case 's':
        {
            off_t offset = getLong(&argv[i][1], GN_ANY_BASE, argv[i]);
            if ((lseek(fd, offset, SEEK_SET)) == -1)
                errExit("lseek");
            printf("%s: seeks succeeded\n", argv[i]);
            break;
        }

        default:
            cmdLineErr("Argument must start with [rRws]: %s\n", argv[i]);
        }
    }

    exit(EXIT_SUCCESS);
}
