/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:21:33 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/10 17:45:40 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/minitalk_bonus.h"

void	signal_ack(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr_fd("Message reçu vers server avec succès\n", 1);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sa;

	check_argument(argc, argv);
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putstr_fd("Erreur : PID Invalide ou Le Processus N'existe Pas\n", 2);
		exit(1);
	}
	sa.sa_handler = signal_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Erreur : Impossible de configurer SIGUSR1 (ack).\n", 2);
		exit(1);
	}
	envoyer_message(pid, argv[2]);
	return (0);
}
