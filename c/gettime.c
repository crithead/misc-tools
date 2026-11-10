#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/time.h>
#include <time.h>

#define BUFFSIZE 4080

//extern int clock_gettime(clockid_t, struct timespec *);
extern int clock_gettime();

static int read_some_data(void)
{
    char buffer[BUFFSIZE] = {0};
    int fd = open("/dev/random", O_RDONLY);
    assert(fd > 0);

    for (int i = 0; i < BUFFSIZE; i++) {
        size_t n = read(fd, (void *)&buffer[i], 1);
        assert(n == 1);
    }

    close(fd);

    int n = 0;
    for (int i = 0; i < BUFFSIZE; i++) {
        n += (int)buffer[i];
    }

    return n;
}

static double timediff(struct timespec *ts1, struct timespec *ts2)
{
    double t1 = (double)ts1->tv_sec + (double)ts1->tv_nsec / 1E9;
    double t2 = (double)ts2->tv_sec + (double)ts2->tv_nsec / 1E9;
    return t2 - t1;
}

int main(int argc, char **argv)
{
    struct timespec t1 = {0};
    struct timespec t2 = {0};

    clock_gettime(CLOCK_REALTIME, &t1);
    int n = read_some_data();
    clock_gettime(CLOCK_REALTIME, &t2);

    printf("N %d\n", n);

    printf("time %f\n", timediff(&t1, &t2));

    return 0;
}

