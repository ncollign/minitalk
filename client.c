#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BITS 8

void handle_signal(int sig)
{
    static int  index;
    static int  byte[MAX_BITS];

    byte = {0};
    index = 0;
    if (sig == SIGUSR1)
    {
        byte |= (0 << bit);
    } else if (sig == SIGUSR2) {
        byte |= (1 << bit); // Met un 1 à la position bit
    }
}


void    main(void)
{
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);


}