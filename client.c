#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BITS 8

typedef struct s_bit_receiver
{
    int byte[MAX_BITS];
    int nb_bit;
} t_bit_receiver;

void handle_signal(int sig)
{
    /*static int  bits[MAX_BITS] = {0};
    static int  index = 0;

    if (sig == SIGUSR1)
        bits[index] = 0;
    else
        bits[index] = 1;
    index++;

    if (bits[MAX_BITS - 1] != NULL)
    {

    }*/
    t_bit_receiver byte;
    if (!byte)
        malloc

    static char *byte;
    static nb_bit;

    if (sig == SIGUSR1)
    {
        byte = byte + '0';
    }
    else
        byte = byte + '1'


}


void    main(void)
{
    pid_t	pid;

    pid = getpid();

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);


}