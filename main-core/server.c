#include "minitalk.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
/*
	This function receive each bit and print a byte when complete
*/
{
	static unsigned int	bits = 0;
	static unsigned int	character = 0;

	(void)info;
    (void)context;

	if (sig == SIGUSR1)
		character += (1 << bits);
	bits++;
	if (bits == 8)
	{
		if (character == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", character);
		bits = 0;
		character = 0;
	}
}

int	main(void)
/*
	This main function displays the PID and create an infinity loop to handle signal
*/
{
	struct sigaction	sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_printf("Error\nSigaction\n");
        exit(EXIT_FAILURE);
    }
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
