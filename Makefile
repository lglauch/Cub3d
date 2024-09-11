NAME	:= cub3D
CFLAGS	:= -Wextra -Wall -Werror -DDEBUG=1
LIBMLX	:= ./MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm libft/libft.a
SRCS	:= src/main.c src/helper.c src/key_functions.c src/key_hooks.c src/minimap.c\
			src/minimap_utils.c
OBJS	:= ${SRCS:.c=.o}

all: clone libmlx $(NAME)

clone:
	@git clone https://github.com/codam-coding-college/MLX42.git || true

libmlx: clone
	@cd $(LIBMLX) && cmake -B build && cmake --build build -j4


%.o: %.c
	@make -C libft
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C libft clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	rm -rf MLX42

re: clean all



