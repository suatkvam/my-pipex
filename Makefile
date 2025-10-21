# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akivam <akivam@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/21 18:50:56 by akivam            #+#    #+#              #
#    Updated: 2025/10/21 18:50:57 by akivam           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex

all: $(NAME)

$(NAME):
	@$(MAKE) -C mandatory

bonus:
	@$(MAKE) -C bonus

clean:
	@$(MAKE) -C mandatory clean
	@$(MAKE) -C bonus clean

fclean:
	@$(MAKE) -C mandatory fclean
	@$(MAKE) -C bonus fclean

re:
	@$(MAKE) -C mandatory re
	@$(MAKE) -C bonus re

.PHONY: all $(NAME) bonus clean fclean re