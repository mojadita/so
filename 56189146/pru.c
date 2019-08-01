#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
       int fd = open("./mpipe", O_WRONLY);
       int i;
       for (i = 1; i < argc; i++)
       {
           int bytes = write(fd, argv[i], strlen(argv[i]) + 1);
           if (bytes <= 0)
           {
               printf("ERROR: write\n");
               close(fd);
               return 1;
           }
           printf("Wrote %d bytes: %s\n", bytes, argv[i]);
       }

       close(fd);
       return 0;
    }

    /* Else perform one read */
    char buf[64];
    int bytes = 0;

    int fd = open("./mpipe", O_RDONLY);
    bytes = read(fd, buf, 64);
    if (bytes <= 0)
    {
        printf("ERROR: read\n");
        close(fd);
        return 1;
    }
    else
    {
        printf("Read %d bytes: %s\n", bytes, buf);
    }

    close(fd);
    return 0;
}
