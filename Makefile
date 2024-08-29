NAME	:= cub3d
CFLAGS	:= -Wextra -Wall -Werror
LIBMLX	:= ./MLX42

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -lm libft/libft.a printf/libftprintf.a
SRCS	:= 
OBJS	:= ${SRCS:.c=.o}

all: clone libmlx $(NAME)

clone:
	@git clone https://github.com/codam-coding-college/MLX42.git || true

libmlx: clone
	@cd $(LIBMLX) && cmake -B build && cmake --build build -j4


%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"
	@make -C printf
	@make -C libft

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make -C libft clean
	@make -C printf clean

fclean: clean
	@rm -rf $(NAME)
	@make -C libft fclean
	@make -C printf fclean
	rm -rf MLX42

re: clean all



