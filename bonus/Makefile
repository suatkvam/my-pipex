NAME = pipex

OBJ_DIR = obj

LIBFT_DIR = libft
FT_PRINTF_DIR = ft_printf

PIPEX_UTILS = create_pipes.c process_manager.c free_pipeline.c child_utils.c
PARSER_SRC = formatted_path.c free_path.c find_command.c open_file.c

SRCS = $(addprefix pipex_utils/, $(PIPEX_UTILS)) \
       $(addprefix parse/, $(PARSER_SRC)) \
		get-next-line/get_next_line_bonus.c \
		get-next-line/get_next_line_utils_bonus.c \
		file_utils.c \
		setup_pipeline.c \
		here_doc.c \
       main.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_LIB = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_FLAGS = -L$(FT_PRINTF_DIR) -lftprintf

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE_FLAGS = -I. -I./libft -I./ft_printf -I./parse -I./pipex_utils -I./get_next_line
CFLAGS += -g -g3
CFLAGS += $(INCLUDE_FLAGS)

RM = rm -f

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) $(LIBFT_LIB) $(FT_PRINTF_LIB)
	@echo "Linking $(NAME)..."
	@$(CC) $(OBJS) $(FT_PRINTF_FLAGS) $(LIBFT_FLAGS) -o $(NAME)
	@echo "\033[32mSuccessfully built $(NAME)!\033[0m"

$(OBJ_DIR)/%.o: %.c $(LIBFT_LIB) $(FT_PRINTF_LIB)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@echo "Building Libft..."
	@make -s -C $(LIBFT_DIR)

$(FT_PRINTF_LIB):
	@echo "Building ft_printf..."""
	@make -s -C $(FT_PRINTF_DIR)

clean:
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) clean; fi
	@if [ -d "$(FT_PRINTF_DIR)" ]; then make -s -C $(FT_PRINTF_DIR) clean; fi
	@$(RM) -r $(OBJ_DIR)
	@echo "Cleaned object files."

fclean: clean
	@if [ -d "$(LIBFT_DIR)" ]; then make -s -C $(LIBFT_DIR) fclean; fi
	@if [ -d "$(FT_PRINTF_DIR)" ]; then make -s -C $(FT_PRINTF_DIR) fclean; fi
	@$(RM) $(NAME)
	@echo "Removed binary: $(NAME)."

re: fclean all

.PHONY: all clean fclean re