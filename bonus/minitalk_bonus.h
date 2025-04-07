/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:53:24 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 17:41:40 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int	bit;
	int	byte_index;
	int	expected_bytes;
	int	client_pid;
}	t_data;

// client_utils
void	check_argument(int argc, char **argv);
void	envoyer_message(int pid, char *message);

// client_utils
void	traiter_signal(int sig, siginfo_t *info, void *context);
void	configurer_signaux(void);
int		ft_which_byte(unsigned char buffer[4]);
void	do_process(t_data *set, unsigned char *buffer);

#endif
