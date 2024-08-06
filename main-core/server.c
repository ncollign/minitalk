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

static t_buffer_node	*g_buffer_node = NULL;

t_buffer_node	*create_node()
/*
	This function creates a node where characters are stored in
*/
{
	t_buffer_node *new_node;

    new_node = malloc(sizeof(t_buffer_node));
    if (!new_node)
    {
        ft_printf("Erreur\nAllocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    new_node->index = 0;
    new_node->next = NULL;
    new_node->buffer[0] = '\0';
    return (new_node);
}

static void	display_message(t_buffer_node *head)
/*
	This function displays the message
*/
{
	t_buffer_node	*temp;
    t_buffer_node	*next_node;

    temp = head;
    while (temp)
    {
        ft_printf("%s", temp->buffer);
		next_node = temp->next;
		free(temp);
		temp = next_node;
    }
	ft_printf("\n");    
}

void append_char(t_buffer_node **head, char c)
/*
	This function appends a char to the linked list
*/
{
	t_buffer_node *current;

    if (*head == NULL)
        *head = create_node();

    current = *head;
    while (current->next != NULL || current->index >= STRING_SIZE)
    {
        if (current->index >= STRING_SIZE)
        {
            if (!current->next)
                current->next = create_node();
            current = current->next;
        }
        else
            break;
    }
    current->buffer[current->index] = c;
    current->index++;
    current->buffer[current->index] = '\0';
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
/*
	This function handles signals from the client
*/
{
	static int bit_count = 0;
    static char cur_char = 0;

    (void)context;
    if (sig == SIGUSR1)
        cur_char |= (1 << bit_count);
    bit_count++;
    if (bit_count == 8)
    {
        if (cur_char == '\0')
        {
            display_message(g_buffer_node);
            g_buffer_node = NULL;  // Reset the global pointer to prevent dangling references
            if (info && info->si_pid != 0)
                kill(info->si_pid, SIGUSR1); // Send acknowledgment to the client
        }
        else
        {
            append_char(&g_buffer_node, cur_char);
        }
        bit_count = 0;
        cur_char = 0;
    }
}

int	main(void)
/*
	Main function
*/
{
	struct sigaction sa;

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    if ((sigaction(SIGUSR1, &sa, NULL) == -1)
        || (sigaction(SIGUSR2, &sa, NULL) == -1))
    {
        ft_printf("Erreur\nSigaction\n");
        exit(EXIT_FAILURE);
    }
    ft_printf("PID du serveur : %d\n", getpid());
    while (1)
        pause();
    return (0);
}
