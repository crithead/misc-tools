/**
 * Print the command line arguments and the environmment of this process.
 */

#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
    assert(argv[argc] == NULL);

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }
    putchar('\n');

    for (int i = 1; envp[i] != NULL; i++) {
        printf("envp[%d] = \"%s\"\n", i, envp[i]);
    }
    putchar('\n');

    return 0;
}
