/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkiviloo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:02:42 by rkiviloo          #+#    #+#             */
/*   Updated: 2022/11/22 18:02:48 by rkiviloo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "../libft/libft.h"
//Need to usleep between sending signals, otherwise comms get jammed. 
int	transmit_char(int pid, int *bits)
{
	int	i;
	int	error_flag;

	i = 0;
	error_flag = 0;
	while (i < 8)
	{
		if (bits[i])
		{
			if (kill(pid, SIGUSR2) == -1)
				error_flag = 1;
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				error_flag = 1;
		}	
		i++;
		usleep(100);
	}
	return (error_flag);
}

void	get_bits(char *str, int pid)
{
	int	bits[8];
	int	bit_index;
	int	error_flag;

	error_flag = 0;
	while (*str)
	{
		bit_index = 0;
		while (bit_index < 8)
		{
			bits[7 - bit_index] = (*str >> bit_index) & 1;
			bit_index++;
		}
		if (transmit_char(pid, bits))
			error_flag = 1;
		str++;
	}
	if (error_flag == 0)
		ft_printf("Message received successfully by the server!");
	else
		ft_printf("Error sending message to server.");
	return ;
}

int	main(int argc, char **argv)
{
	char	*str;
	int		pid;

	if (argc != 3)
	{
		ft_printf("ERROR. Usage: ./client <server PID> <string>");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid < 2)
	{
		ft_printf("ERROR. Invalid PID.");
		return (2);
	}
	str = argv[2];
	get_bits(str, pid);
	return (0);
}
