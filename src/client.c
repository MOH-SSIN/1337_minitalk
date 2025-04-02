/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:20:09 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/02 12:22:22 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../src/minitalk.h"


int	main(int argc, char **argv)
{
	int	pid;

	check_argument(argc, argv);
	pid  = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_putstr_fd("Erreur : Le PID Invalide ou Le Processus N'existe Pas\n",2);
		exit(1);
	}
	envoyer_message(pid, argv[2]);
	return (0);
}

//hade cas wach 5asni ndwzha ./client " 83843" MOHcine