/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:49:00 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 13:09:34 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/minitalk_bonus.h"

void	traiter_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	received_char = 0;
	static int	pid = 0;

	(void)context;
	if (pid != info->si_pid)
	{
		pid = info->si_pid;
		bit_count = 0;
		received_char = 0;
	}
	if (sig == SIGUSR2)
		received_char |= (1 << (7 - bit_count));
	bit_count++;
	if (bit_count == 8) // Message complet reçu
    {
		//hadi li zate !! ack
        if (received_char == '\0')  // Si c'est le caractère de fin de message
        {
            kill(pid, SIGUSR1);  // Envoie de l'ACK au client
			// exit(1);
        }
        write(1, &received_char, 1); // Affiche le message reçu
        bit_count = 0;
        received_char = 0;
    }
}

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
