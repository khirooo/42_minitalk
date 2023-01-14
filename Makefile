# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 20:31:43 by kfergani          #+#    #+#              #
#    Updated: 2022/07/25 18:43:03 by kfergani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	server client
BONUS	= 	server_bonus client_bonus
LIBFT	=	libftprintf.a
PRINTF_DIR	=	./ft_printf
INCLUDE	=	includes
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror
SOURCES = server.c client.c
BONUS_SPURCES = server_bonus.c client_bonus.c
SRCDIR	=	src
OBJDIR	=	obj
BONUSDIR = bonus
BNS_SRC = $(addprefix $(BONUSDIR)/, $(BONUS_SPURCES))
BNS_OBJ = $(addprefix $(BONUSDIR)/, $(BONUS_SPURCES:.c=.o))
SRCS	=	$(addprefix $(SRCDIR)/, $(SOURCES))
OBJS	=	$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))

all : $(NAME)

bonus : $(BONUS)

$(BONUS) :: $(BNS_OBJ) $(LIBFT)
	CC -o server_bonus $(BONUSDIR)/server_bonus.o $(LIBFT)
	CC -o client_bonus $(BONUSDIR)/client_bonus.o $(LIBFT)

$(NAME)	:: 	$(OBJS) $(LIBFT)
	CC -o server $(OBJDIR)/server.o $(LIBFT)
	CC -o client $(OBJDIR)/client.o $(LIBFT)

$(OBJDIR)/%.o : $(SRCDIR)/%.c 
	mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -o $@ -c $< 

$(BONUSDIR)/%.o : $(BONUSDIR)/%.c 
	$(CC) $(FLAGS) -o $@ -c $< 

$(LIBFT) : $(PRINTF_DIR)
	make -C $(PRINTF_DIR)
	cp	$(PRINTF_DIR)/libftprintf.a ./

clean:
	make clean -C $(PRINTF_DIR)
	rm -rf $(BNS_OBJ)
	rm -rf $(OBJDIR)
	rm -rf $(LIBFT)

fclean:	clean
	make fclean -C $(PRINTF_DIR)
	rm -rf $(NAME)
	rm -rf $(BONUS)
re	: fclean all
