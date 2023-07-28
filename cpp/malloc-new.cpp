// Test mixing use of malloc/free with new/delete
//
// g++ -Wall -std=c++11 -O2 -g malloc-new.cpp -o malloc-new
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>

#include <signal.h>

struct thing {
    char a;
    unsigned char b;
    short c;
    int d;
};

static struct thing THING0 = { 'A', 'B', 0x0CCC, 0x0DDDDDDD };


void handle_signal(int);
void print_thing(struct thing *);
void use_malloc_free(void);
void use_new_delete(void);
void use_malloc_delete(void);
void use_new_free(void);
void segv(void);


int main(int argc, char **argv)
{
    signal(SIGSEGV, handle_signal);
    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_signal);
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    print_thing(&THING0);

    use_malloc_free();
    use_new_delete();
    use_new_free();
    use_malloc_delete();

    segv();

    return 0;
}


void handle_signal( int sig )
{
    switch (sig) {
    case SIGSEGV:
        std::cout << "SEGV" << std::endl;
        exit(sig);
        break;
    case SIGINT:
        std::cout << "INT" << std::endl;
        exit(sig);
        break;
    case SIGHUP:
        std::cout << "HUP" << std::endl;
        break;
    case SIGUSR1:
        std::cout << "USR1" << std::endl;
        break;
    case SIGUSR2:
        std::cout << "USR2" << std::endl;
        break;
    default:
        std::cout << "SIG (" << sig << ")" << std::endl;
        break;
    }
}


void print_thing(struct thing *t)
{
    printf("thing( a=%c, b=%c, c=%04X, d=%08X )\n", t->a, t->b, t->c, t->d);
}


void use_malloc_free(void)
{
    std::cout << __FUNCTION__ << std::endl;

    struct thing *t = (struct thing *)malloc(sizeof(struct thing));
    memcpy(t, &THING0, sizeof(struct thing));
    print_thing(t);
    free(t);
}


void use_new_delete(void)
{
    std::cout << __FUNCTION__ << std::endl;

    struct thing *t = new struct thing;
    memcpy(t, &THING0, sizeof(struct thing));
    print_thing(t);
    delete t;
}


void use_new_free(void)
{
    std::cout << __FUNCTION__ << std::endl;

    struct thing *t = new struct thing;
    memcpy(t, &THING0, sizeof(struct thing));
    print_thing(t);
    t->a = 'J';
    t->b = 'Q';
    t->c = 0x1234;
    t->d = 0x5A5A5A5A;
    print_thing(t);
    free(t);
}


void use_malloc_delete(void)
{
    std::cout << __FUNCTION__ << std::endl;

    struct thing *t = (struct thing *)malloc(sizeof(struct thing));
    memcpy(t, &THING0, sizeof(struct thing));
    print_thing(t);
    t->a = '?';
    t->b = '#';
    t->c = 0x5678;
    t->d = 0x0000AAAA;
    print_thing(t);
    delete t;
}


void segv(void)
{
    int *t = nullptr;
    *t = 5;
}

