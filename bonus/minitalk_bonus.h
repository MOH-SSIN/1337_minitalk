/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:53:24 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 13:10:02 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include "../libft/libft.h"

// client_utils
void	check_argument(int argc, char **argv);
void	envoyer_message(int pid, char *message);

// server_utils
void	traiter_signal(int sig, siginfo_t *info, void *context);
void	configurer_signaux(void);

#endif
