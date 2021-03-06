mmap_test.c                                                                                         0000644 0000144 0000012 00000002205 13214232155 0013516 0                                                                                                    ustar 00nasko                           staff                           0000465 0200012                                                                                                                                                                        #include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(void) {
	int fd, r = 0;
	off_t size;
	size_t j;
	void *map;
	char *cmap;
	pid_t pid;
	
	fd = open("mmap_test", O_RDWR);
	if (fd < 0) {
		perror("open");
		r = -1;
		goto bad0;
	}
	
	size = lseek(fd, 0, SEEK_END);
	if (size < 0) {
		perror("lseek");
		r = -1;
		goto bad1;
	}
	
	map = mmap(NULL, (size_t)size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) {
		perror("mmap");
		r = -1;
		goto bad1;
	}
	
	if (mprotect(map, (size_t)size, PROT_READ | PROT_WRITE) < 0) {
		perror("mprotect");
	}
	
	cmap = (char *)map;
	
	pid = fork();
	if (!pid) { /* child */
		for (j = 0; j < (size_t)size; j++) {
			cmap[j] = (j & 1) ? 'D' : 'C';
			sleep(1);
		}
	} if (pid > 0) {
		while (1) {
			for (j = 0; j < (size_t)size; j++)
				fputc(cmap[j], stdout);
			fputc('\n', stdout);
			sleep(1);
		}
	} else {
		perror("fork");
		r = -1;
	}
	
	if (munmap(map, (size_t)size) < 0) {
		perror("munmap");
		r = -1;
	}
	
bad1:
	close(fd);
bad0:
	return r;
}

                                                                                                                                                                                                                                                                                                                                                                                           mmap_test                                                                                           0000644 0000144 0000012 00000002000 13214232210 0013256 0                                                                                                    ustar 00nasko                           staff                           0000465 0200012                                                                                                                                                                        aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
read_pseudocode                                                                                     0000644 0000144 0000012 00000000227 13214233570 0014435 0                                                                                                    ustar 00nasko                           staff                           0000465 0200012                                                                                                                                                                        fd = open(...);
lseek(fd, off, SEEK_SET);
read(fd, buf, len);

fd = open(...);
buf = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, offset);
                                                                                                                                                                                                                                                                                                                                                                         signal.c                                                                                            0000644 0000144 0000012 00000000433 13214227745 0013014 0                                                                                                    ustar 00nasko                           staff                           0000465 0200012                                                                                                                                                                        #include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighnd(int sig) {
	printf("Caught signal %d\n", sig);
	fflush(stdout);
	signal(SIGTERM, &sighnd);
	return;
}

int main(int argc, char *argv[]) {
	signal(SIGTERM, &sighnd);
	while (1)
		sigpause(SIGTERM);
	return 0;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     