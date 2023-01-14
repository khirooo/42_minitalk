/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:05:02 by kfergani          #+#    #+#             */
/*   Updated: 2022/07/25 18:34:54 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	confirmation(int sig)
{
	if (sig < 0)
		exit(1);
	ft_printf("Message received\n");
	exit(0);
}

void	send_message(int server_id, char *message)
{
	size_t	i;
	uint8_t	byte;

	i = 0;
	while (i <= ft_strlen(message))
	{
		byte = 1 << 7;
		while (byte)
		{
			if (byte & (unsigned char)message[i])
				kill(server_id, SIGUSR1);
			else
				kill(server_id, SIGUSR2);
			byte >>= 1;
			usleep(500);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			server_id;
	char		*message;

	if (argc != 3)
	{
		ft_printf("Wrong arguments, i am leaving!\n");
		exit(1);
	}
	else
	{
		server_id = ft_atoi(argv[1]);
		message = ft_strdup(argv[2]);
	}
	if (server_id >= 4194305 || server_id < 0 || !message)
		exit(1);
	signal(SIGUSR1, confirmation);
	send_message(server_id, message);
	free(message);
	pause();
	return (0);
}
