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