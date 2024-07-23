/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:44:56 by ncollign          #+#    #+#             */
/*   Updated: 2024/07/09 11:44:57 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

#define WAIT_TIME 400

static volatile sig_atomic_t received_confirmation = 0;

static void confirmation_handler(int sig)
/*
	This function handles confirmation message
*/
{
	(void)sig;
	received_confirmation = 1;
}

static void send_char(pid_t server_pid, unsigned char c)
/*
	This function sends a char to server PID
*/
{
	int bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(WAIT_TIME);
		bit++;
	}
}

static void send_message(pid_t server_pid, unsigned char *message)
/*
	This function cuts a string into chars, then sends each char to server PID
*/
{
	int i;

	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
}

int main(int argc, char **argv)
/*
	This function verifies input
	Then send a message to the server PID
*/
{
	int server_pid;
	struct sigaction sa;

	if (argc != 3)
	{
		ft_printf("Error\nUsage : %s <server_pid> <message>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	sa.sa_handler = confirmation_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_printf("Error\nSigaction\n");
		return (EXIT_FAILURE);
	}
	send_message(server_pid, (unsigned char *)(argv[2]));
	while (!received_confirmation)
		pause();
	ft_printf("Message received by server.\n");
	return (EXIT_SUCCESS);
}
