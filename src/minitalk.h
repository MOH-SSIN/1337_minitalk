/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:20:13 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/03 17:03:53 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

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
