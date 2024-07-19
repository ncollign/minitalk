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

#define MAX_CAPACITY 256

typedef struct s_data
{
    unsigned int bits;
    unsigned int character;
    unsigned int length;
    char *message;
} t_data;

static void display_message(t_data *data)
{
    if (data->message)
    {
        ft_printf("%s", data->message);
        free(data->message);
        data->message = NULL;
        data->length = 0;
    }
}

static void add_character(t_data *data, char character)
{
    data->message[data->length] = character;
    data->length++;
    data->message[data->length] = '\0';
	if (data->length + 1 >= MAX_CAPACITY)
    {
        display_message(data);
        data->message = malloc(MAX_CAPACITY + 1);
        if (!data->message)
        {
            ft_printf("Error\nMemory allocation error\n");
            exit(EXIT_FAILURE);
        }
        data->message[0] = '\0';
    }
}

static void handle_signal(int sig, siginfo_t *info, void *context)
{
    static t_data data = {0, 0, 0, NULL};

    (void)info;
    (void)context;
    if (data.message == NULL)
    {
        data.message = malloc(MAX_CAPACITY + 1);
        if (!data.message)
        {
            ft_printf("Error\nMemory allocation error\n");
            exit(EXIT_FAILURE);
        }
        data.message[0] = '\0';
    }
    if (sig == SIGUSR1)
        data.character |= (1 << data.bits);
    data.bits++;
    if (data.bits == 8)
    {
        if (data.character == '\0' || data.character == '\n')
        {
            display_message(&data);
            ft_printf("\n");
        }
        else
        {
            add_character(&data, data.character);
        }
        data.bits = 0;
        data.character = 0;
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
        pause();
    return (0);
}