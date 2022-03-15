# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbrito-l <cbrito-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/11 12:38:14 by cbrito-l          #+#    #+#              #
#    Updated: 2022/03/15 23:45:09 by cbrito-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

HEADER		=	.

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -g -I $(HEADER) -pthread

SRCS		=	philosophers.c \
				threads.c \
				init.c \
				utils.c \
				libft_a.c \
				libft_b.c \
				libft_c.c \


OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all
