/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkiviloo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:03:07 by rkiviloo          #+#    #+#             */
/*   Updated: 2022/11/22 18:03:24 by rkiviloo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <signal.h>
#define _XOPEN_SOURCE 700

int	pwr_two(int p)
{
	int	result;

	result = 2;
	if (p == 0)
		return (1);
	while (p > 1)
	{
		result *= 2;
		p--;
	}
	return (result);
}

void	print_binary(int *bits)
{
	int	i;
	int	p;
	int	result;

	p = 0;
	i = 7;
	result = 0;
	while (i >= 0)
	{
		result += bits[i] * pwr_two(p);
		i--;
		p++;
	}
	ft_printf("%c", result);
}

void	sigusr_handler(int signum)
{
	static int	bitsreceived;
	static int	bits[8];

	if (signum == SIGUSR1)
	{
		bits[bitsreceived] = 0;
		bitsreceived++;
	}
	else if (signum == SIGUSR2)
	{
		bits[bitsreceived] = 1;
		bitsreceived++;
	}
	if (bitsreceived == 8)
	{
		print_binary(bits);
		bitsreceived = 0;
	}
	return ;
}

int	main(void)
{
	int					srv_pid;
	struct sigaction	act_sigusr;

	act_sigusr.sa_handler = sigusr_handler;
	sigemptyset(&act_sigusr.sa_mask);
	act_sigusr.sa_flags = 0;
	srv_pid = getpid();
	ft_printf("PID: %i\n", srv_pid);
	if (sigaction(SIGUSR1, &act_sigusr, NULL) == -1)
		ft_printf("Sigaction error. (SIGUSR1)");
	if (sigaction(SIGUSR2, &act_sigusr, NULL) == -1)
		ft_printf("Sigaction error. (SIGUSR2)");
	while (1)
		pause();
}
