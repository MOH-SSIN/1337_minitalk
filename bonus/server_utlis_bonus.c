/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utlis_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:49:00 by mez-zahi          #+#    #+#             */
/*   Updated: 2025/04/07 17:17:20 by mez-zahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bonus/minitalk_bonus.h"



// Fonction pour déterminer le nombre d'octets attendus pour un caractère UTF-8
int ft_which_byte(unsigned char buffer[4])
{
    int expected_bytes;

    expected_bytes = 0;
    if ((buffer[0] & 128) == 0)
        expected_bytes = 1;
    else if ((buffer[0] & 224) == 192)
        expected_bytes = 2;
    else if ((buffer[0] & 240) == 224)
        expected_bytes = 3;
    else if ((buffer[0] & 248) == 240)
        expected_bytes = 4;
    return (expected_bytes);
}

void do_process(t_data *set, unsigned char *buffer)
{
    if (set->bit == 8)
    {
        set->bit = 0;
        if (set->byte_index == 0)
            set->expected_bytes = ft_which_byte(buffer);
        (set->byte_index)++;
        
        if (set->byte_index == set->expected_bytes)
        {
            // Si c'est la fin du message (caractère nul)
            if (buffer[0] == '\0')
            {
                write(1, "\n", 1);
                kill(set->client_pid, SIGUSR1);  // Envoie de l'ACK au client
            }
            else
                write(1, buffer, set->expected_bytes);
            
            // Réinitialiser pour le prochain caractère
            set->byte_index = 0;
            ft_memset(buffer, 0, 4);
        }
        // Si on a reçu un caractère nul (fin de message)
        else if (buffer[set->byte_index - 1] == '\0')
        {
            set->byte_index = 0;
            ft_memset(buffer, 0, 4);
        }
    }
}

void traiter_signal(int sig, siginfo_t *info, void *context)
{
    static unsigned char buffer[4] = {0};
    static t_data set = {0, 0, 0, 0};
    
    (void)context;
    
    // Si c'est un nouveau client, réinitialiser les variables
    if (set.client_pid != info->si_pid)
    {
        set.client_pid = info->si_pid;
        set.bit = 0;
        set.byte_index = 0;
        set.expected_bytes = 0;
        ft_memset(buffer, 0, 4);
    }
    
    // Traiter le bit reçu
    if (sig == SIGUSR2)
        buffer[set.byte_index] = (buffer[set.byte_index] << 1) | 1;
    else if (sig == SIGUSR1)
        buffer[set.byte_index] = (buffer[set.byte_index] << 1);
    
    set.bit++;
    do_process(&set, buffer);
}

void configurer_signaux(void)
{
    struct sigaction sa;

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

