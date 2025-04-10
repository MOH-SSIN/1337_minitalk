# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mez-zahi <mez-zahi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 10:21:30 by mez-zahi          #+#    #+#              #
#    Updated: 2025/04/10 17:44:00 by mez-zahi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

HEADER = src/minitalk.h libft/libft.h
HEADER_BONUS = bonus/minitalk_bonus.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_CLIENT = src/client.c src/client_utlis.c
SRCS_SERVER = src/server.c src/server_utlis.c

SRCS_CLIENT_BONUS = bonus/client_bonus.c bonus/client_utlis_bonus.c
SRCS_SERVER_BONUS = bonus/server_bonus.c bonus/server_utlis_bonus.c

OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)

$(LIBFT): $(LIBFT_DIR)/*.c $(LIBFT_DIR)/*.h
	@make -C $(LIBFT_DIR)

$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(OBJS_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT)
	$(CC) $(OBJS_SERVER) $(LIBFT) -o $(NAME_SERVER)

bonus: $(LIBFT) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS) $(LIBFT)
	$(CC) $(OBJS_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS) $(LIBFT)
	$(CC) $(OBJS_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)

%.o: %.c $(HEADER) $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS) $(LIBFT)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re
