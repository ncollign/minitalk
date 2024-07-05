#include "minitalk.h"

void	send_char(pid_t server_pid, unsigned char c)
/*
	This function sends a char to server PID
*/
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
			{
				ft_printf("Error\nSignal sending failed\n");
				exit(EXIT_FAILURE);
			}
			else
				ft_printf("Bit sent : '1'\n");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
			{
				ft_printf("Error\nSignal sending failed\n");
				exit(EXIT_FAILURE);
			}
			else
				ft_printf("Bit sent : '0'\n");
		}
		usleep(100);
		bit++;
	}
}

void	send_message(pid_t server_pid, unsigned char *message)
/*
    This function cuts a string into chars, then sends each char to server PID
*/
{
	int				i;

	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0'); // Send null character to indicate the end of the message
}

int	main(int argc, char **argv)
/*
	This function verifies input
	Then send a message to the server PID
*/
{
	int	server_pid;

	if (argc != 3)
	{
		fprintf(stderr, "Usage : %s <server_pid> <message>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	server_pid = atoi(argv[1]);
	send_message(server_pid, (unsigned char *)(argv[2]));
	return (EXIT_SUCCESS);
}
