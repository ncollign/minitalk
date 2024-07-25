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

#define MAX_CAPACITY 32
#define TIMEOUT 1

static t_data	g_data = {NULL, 0, 0, 0, 0, 0};

static void	display_message(void)
/*
	This function displays a message
*/
{
	if (g_data.message)
	{
		ft_printf("%s", g_data.message);
		g_data.length = 0;
		g_data.message[g_data.length] = '\0';
	}
}

static void	add_character(void)
/*
	This function adds a character into g_g_data
	Prints the part of the message if bigger than MAX_CAPACITY
*/
{
	g_data.message[g_data.length] = g_data.character;
	g_data.length++;
	g_data.message[g_data.length] = '\0';
	if (g_data.length >= MAX_CAPACITY)
		display_message();
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
/*
	This function handles signal from the client
*/
{
	(void)context;
	g_data.received_signal = 1;
	if (g_data.message == NULL)
	{
		g_data.message = (char *)malloc(MAX_CAPACITY + 1);
		if (!g_data.message)
		{
			ft_printf("Error\nMemory allocation error\n");
			exit(EXIT_FAILURE);
		}
		g_data.message[0] = '\0';
	}
	if (info && info->si_pid != 0)
		g_data.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		g_data.character += (1 << g_data.bits);
	g_data.bits++;
	if (g_data.bits == 8)
	{
		if (g_data.character == '\0' || g_data.character == '\n')
		{
			display_message();
			ft_printf("\n");
			if (g_data.client_pid != 0)
				kill(g_data.client_pid, SIGUSR1);
			if (g_data.character == '\0')
			{
				free(g_data.message);
				g_data.message = NULL;
			}
		}
		else
			add_character();
		g_data.bits = 0;
		g_data.character = 0;
	}
}

static void	reset_g_data(void)
/*
	This function resets all the g_data if no message is sent
*/
{
	if (g_data.message)
	{
		free(g_data.message);
		g_data.message = NULL;
		ft_printf("\n");
		g_data.bits = 0;
		g_data.character = 0;
		g_data.length = 0;
		g_data.client_pid = 0;
		g_data.received_signal = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	if ((sigaction(SIGUSR1, &sa, NULL) == -1)
		|| (sigaction(SIGUSR2, &sa, NULL) == -1))
	{
		ft_printf("Error\nSigaction\n");
		exit(EXIT_FAILURE);
	}
	ft_printf("Server PID: %d\n", getpid());
	while (1)
	{
		sleep(TIMEOUT);
		if (!g_data.received_signal)
			reset_g_data();
		g_data.received_signal = 0;
	}
	return (0);
}
