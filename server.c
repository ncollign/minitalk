#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void	handle_signal(int sig)
{
	static int	bit = 0;
	static int	character = 0;

	if (sig == SIGUSR1)
		character += (1 << bit);  // Utilisation de += pour mettre à jour le bit correspondant
	bit++;
	if (bit == 8)
	{
		if (character == '\0')
			write(1, "\n", 1);  // Fin de chaîne
		else
			write(1, &character, 1);  // Afficher le caractère reçu
		bit = 0;
		character = 0;
	}
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	printf("Server PID: %d\n", pid);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}