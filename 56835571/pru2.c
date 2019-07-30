	#include <stdio.h>
    #include <fcntl.h>
    #include <unistd.h>
	#include <sys/stat.h>
    int main()
    {
        int fd = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0666);
        lseek(fd, 1000000, SEEK_SET);
        char string[] = "Hello, world";
        write(fd, string, sizeof string);
		struct stat st;
		fstat(fd, &st);
	#define P(_f) printf(#_f ": %lu\n", (unsigned long)st._f)
		P(st_dev);
		P(st_ino);
		P(st_nlink);
		P(st_uid);
		P(st_gid);
		P(st_rdev);
		P(st_size);
		P(st_blksize);
		P(st_blocks);
		P(st_flags);
		P(st_gen);
        close(fd);
    }
