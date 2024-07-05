#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

void	send_char(pid_t server_pid, char c)
{
	for (int i = 0; i < 8; i++)
	{
		if (c & (1 << i))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
	}
}

void	send_string(pid_t server_pid, char *str)
{
	while (*str)
	{
		send_char(server_pid, *str);
		str++;
	}
	send_char(server_pid, '\0');  // Envoyer le caractère nul pour indiquer la fin de la chaîne
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	pid_t	server_pid = atoi(argv[1]);
	char	*message = argv[2];

	send_string(server_pid, message);
	return (0);
}