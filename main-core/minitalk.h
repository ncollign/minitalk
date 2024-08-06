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

# define STRING_SIZE 1000
typedef struct	s_buffer_node
{
    char				buffer[STRING_SIZE + 1];
	int					index;
    struct s_buffer_node	*next;
} 				t_buffer_node;

#endif