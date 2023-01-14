/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 14:45:23 by kfergani          #+#    #+#             */
/*   Updated: 2022/07/07 18:39:56 by kfergani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_message	g_message[4194305];

void	one_bit_handler(int sig, siginfo_t *info, void *contex)
{
	if (sig < 0)
		exit(1);
	contex = NULL;
	g_message[info ->si_pid].c <<= 1;
	g_message[info ->si_pid].c += 1;
	g_message[info ->si_pid].bit_counter++;
	if (g_message[info ->si_pid].bit_counter == 8)
	{
		g_message[info ->si_pid].message[g_message[info ->si_pid].char_counter]
			= g_message[info ->si_pid].c;
		g_message[info ->si_pid].char_counter++;
		g_message[info ->si_pid].bit_counter = 0;
		g_message[info ->si_pid].c = 0;
	}
}

void	zero_bit_handler(int sig, siginfo_t *info, void *contex)
{
	if (sig < 0)
		exit(1);
	contex = NULL;
	g_message[info ->si_pid].c <<= 1;
	g_message[info ->si_pid].bit_counter++;
	if (g_message[info ->si_pid].bit_counter == 8)
	{
		g_message[info ->si_pid].message[g_message[info ->si_pid].char_counter]
			= g_message[info ->si_pid].c;
		if (g_message[info ->si_pid].c == 0)
		{
			ft_printf("I have Received: %s\n", g_message[info ->si_pid].message);
			kill(info ->si_pid, SIGUSR1);
			g_message[info ->si_pid].char_counter = -1;
		}
		g_message[info ->si_pid].char_counter++;
		g_message[info ->si_pid].bit_counter = 0;
		g_message[info ->si_pid].c = 0;
	}
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	one_bit;
	struct sigaction	zero_bit;

	one_bit.sa_sigaction = one_bit_handler;
	zero_bit.sa_sigaction = zero_bit_handler;
	sigemptyset (&one_bit.sa_mask);
	sigemptyset (&zero_bit.sa_mask);
	one_bit.sa_flags = SA_SIGINFO;
	zero_bit.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &one_bit, NULL);
	sigaction(SIGUSR2, &zero_bit, NULL);
	pid = getpid();
	if (pid < 0)
	{
		ft_printf("Enable to get Process ID, am out!\n");
		exit(1);
	}
	else
		ft_printf("My ID is: %d\n", pid);
	while (1)
		pause();
	return (0);
}
