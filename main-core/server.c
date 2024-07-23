#include "minitalk.h"

#define MAX_CAPACITY 32
#define TIMEOUT 1

typedef struct s_data
{
    char            *message;
    unsigned int    bits;
    unsigned int    character;
    unsigned int    length;
    pid_t           client_pid;
    int             received_signal;
} t_data;

static t_data data = {NULL, 0, 0, 0, 0, 0};

static void display_message()
/*
    This function displays a message
*/
{
    if (data.message)
    {
        ft_printf("%s", data.message);
        data.length = 0;
        data.message[data.length] = '\0';
    }
}

static void add_character()
/*
	This function adds a character into data
	Prints the part of the message if bigger than MAX_CAPACITY
*/
{
    data.message[data.length] = data.character;
    data.length++;
    data.message[data.length] = '\0';
    if (data.length >= MAX_CAPACITY)
        display_message();
}

static void handle_signal(int sig, siginfo_t *info, void *context)
/*
	This function handles signal from the client
*/
{
    (void)context;
    data.received_signal = 1;
    if (data.message == NULL)
    {
        data.message = (char *)malloc(MAX_CAPACITY + 1);
        if (!data.message)
        {
            ft_printf("Error\nMemory allocation error\n");
            exit(EXIT_FAILURE);
        }
        data.message[0] = '\0';
    }
    if (info && info->si_pid != 0)
        data.client_pid = info->si_pid;
    if (sig == SIGUSR1)
        data.character += (1 << data.bits);
    data.bits++;
    if (data.bits == 8)
    {
        if (data.character == '\0' || data.character == '\n')
        {
            display_message(&data);
            ft_printf("\n");
            if (data.client_pid != 0)
                kill(data.client_pid, SIGUSR1);
            if (data.character == '\0')
            {
                free(data.message);
                data.message = NULL;
            }
        }
        else
            add_character(&data);
        data.bits = 0;
        data.character = 0;
    }
}

static void reset_data()
/*
	This function resets all the data if no message is sent
*/
{
    if (data.message)
    {
        free(data.message);
        data.message = NULL;
		ft_printf("\n");
		data.bits = 0;
		data.character = 0;
		data.length = 0;
		data.client_pid = 0;
		data.received_signal = 0;
    }
}

int main(void)
{
    struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    if ((sigaction(SIGUSR1, &sa, NULL) == -1) || (sigaction(SIGUSR2, &sa, NULL) == -1))
    {
        ft_printf("Error\nSigaction\n");
        exit(EXIT_FAILURE);
    }
    ft_printf("Server PID: %d\n", getpid());
    while (1)
    {
        sleep(TIMEOUT);
        if (!data.received_signal)
            reset_data();
        data.received_signal = 0;
    }
    return (0);
}
