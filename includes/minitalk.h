/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:54:02 by kfergani          #+#    #+#             */
/*   Updated: 2022/07/07 21:07:15 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "ft_printf.h"
# include <unistd.h>
# include <signal.h>

# define MAX_LENGTH 1000000

typedef struct s_message
{
	char	message[MAX_LENGTH];
	int		c;
	int		bit_counter;
	int		char_counter;
}	t_message;

#endif
