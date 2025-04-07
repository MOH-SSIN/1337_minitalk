/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:53:41 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 13:09:41 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/minitalk_bonus.h"

int	est_digit(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_argument(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Erreur : Usage Corect -> ./client <PID> <message>\n", 2);
		exit(1);
	}
	if (!est_digit(argv[1]))
	{
		ft_putstr_fd("Erreur : PID Doit Etre Une Nombre Entier positif\n", 2);
		exit(1);
	}
	if (!argv[2] || !argv[2][0])
	{
		ft_putstr_fd("Erreur : Le Message Ne Peut pas Etre Vide\n", 2);
		exit(1);
	}
}

void	envoyer_bit(int pid, char bit)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((bit >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(500);
		usleep(500);
		i--;
	}
}

void	envoyer_message(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
	{
		envoyer_bit(pid, message[i]);
		i++;
	}
	envoyer_bit(pid, '\0');
}
// for i in {1..20}; do "string"; done