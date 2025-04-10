/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:49:00 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 17:39:07 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/minitalk_bonus.h"

//Fonction pour déterminer le nombre d'octets attendus pour un caractère UTF-8
int	ft_which_byte(unsigned char buffer[4])
{
	int	expected_bytes;

	expected_bytes = 0;
	if ((buffer[0] & 128) == 0)//10000000 = 128
		expected_bytes = 1;
		
	else if ((buffer[0] & 224) == 192)//11100000 = 224
		expected_bytes = 2;

	else if ((buffer[0] & 240) == 224)//11110000 = 240
		expected_bytes = 3;

	else if ((buffer[0] & 248) == 240)//11111000 = 248
		expected_bytes = 4;
	return (expected_bytes);
}

//Gère le traitement d'un caractère une fois qu'il est entièrement reçu.
void	do_process(t_data *set, unsigned char *buffer)
{
	if (set->bit == 8)
	{
		set->bit = 0;
		if (set->byte_index == 0)
			set->expected_bytes = ft_which_byte(buffer);
		(set->byte_index)++;
		if (set->byte_index == set->expected_bytes)
		{
			if (buffer[0] == '\0')
			{
				// write(1, "\n", 1);
				kill(set->client_pid, SIGUSR1);
			}
			else
				write(1, buffer, set->expected_bytes);
			set->byte_index = 0;
			ft_memset(buffer, 0, 4);
		}
		else if (buffer[set->byte_index - 1] == '\0')
		{
			set->byte_index = 0;
			ft_memset(buffer, 0, 4);
		}
	}
}

//Gère les signaux SIGUSR1 et SIGUSR2 reçus.
void	traiter_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	buffer[4] = {0};
	static t_data			set = {0, 0, 0, 0};

	(void)context;
	if (set.client_pid != info->si_pid)
	{
		set.client_pid = info->si_pid;
		set.bit = 0;
		set.byte_index = 0;
		set.expected_bytes = 1;// normalement 1 d
		ft_memset(buffer, 0, 4);
	}
	if (sig == SIGUSR2)
		buffer[set.byte_index] = (buffer[set.byte_index] << 1) | 1;
	else if (sig == SIGUSR1)
		buffer[set.byte_index] = (buffer[set.byte_index] << 1);
	set.bit++;
	do_process(&set, buffer);
}

//Configure les signaux SIGUSR1 et SIGUSR2 apartir traiter_signal.
void	configurer_signaux(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = traiter_signal;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Erreur : Impossible de configurer SIGUSR1.\n", 2);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Erreur : Impossible de configurer SIGUSR2.\n", 2);
		exit(1);
	}
}
