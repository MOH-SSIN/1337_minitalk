/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:21:33 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 13:09:28 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/minitalk_bonus.h"

void signal_ack(int sig)
{
    if (sig == SIGUSR1)
    {
        ft_putstr_fd("Message reçu avec succès\n", 1);
    }
}

int	main(int argc, char **argv)
{
	int	pid;

	check_argument(argc, argv);
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putstr_fd("Erreur : PID Invalide ou Le Processus N'existe Pas\n", 2);
		exit(1);
	}
	// Configuration du signal d'ACK
    struct sigaction sa;
    sa.sa_handler = signal_ack;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGUSR1, &sa, NULL);

	//deja cant
    envoyer_message(pid, argv[2]);

    // Attente du signal ACK
    pause();  // Le client attend jusqu'à ce qu'il reçoive un SIGUSR1
	return (0);
}