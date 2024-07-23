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

#ifndef MINITALK_H
# define MINITALK_H
# include "../libft/libft.h"

# include <signal.h>
# include <sys/types.h>
# include <string.h>
# include <stdio.h>

typedef struct s_data
{
	char			*message;
	unsigned int	bits;
	unsigned int	character;
	unsigned int	length;
	pid_t			client_pid;
	int				received_signal;
}	t_data;

#endif